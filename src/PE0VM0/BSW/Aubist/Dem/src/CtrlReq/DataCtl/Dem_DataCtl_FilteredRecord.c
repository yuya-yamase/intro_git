/* Dem_DataCtl_FilteredRecord_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_FilteredRecord/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_DTC.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFFRecNumByRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetNonObdFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByTSFFListIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC) TSFFRecIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC) RecordNumberPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByTSFFListRecIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);
static FUNC( Dem_u16_TSFFDIndexType, DEM_CODE ) Dem_Data_GetStartIndexOfTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecIndex
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFStartRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
);
static FUNC( void, DEM_CODE ) Dem_Data_UpdateIndexForSearchTSFFRecNum
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
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

/****************************************************************************/
/* Function Name | Dem_Data_GetNumberOfFilteredRecords                      */
/* Description   | Gets the number of filtered records.                     */
/* Preconditions |                                                          */
/* Parameters    | [out] NumberOfFilteredRecordsPtr :                       */
/*               |        The number of filtered records.                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetNumberOfFilteredRecords
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    /* Stores NumberOfFilteredRecords. */
    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    *NumberOfFilteredRecordsPtr = obdFFDRecordNum + nonObdFFDRecordNum;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetFilteredRecord                               */
/* Description   | Gets the filtered freeze frame record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        DTCFormat type of Dem's external definition.      */
/*               | [in] FaultIndex :                                        */
/*               |        The index corresponding to the specified and nex- */
/*               |        t fault record.                                   */
/*               | [in/out] ObdRecordNumberIndexPtr :                       */
/*               |        The index corresponding to the specified and nex- */
/*               |        t OBD record number.                              */
/*               | [in/out] RecordNumberIndexPtr :                          */
/*               |        The index corresponding to the specified and nex- */
/*               |        t record number.                                  */
/*               | [in/out] TSFFListIndexPtr :                              */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_NG : Retrieving the filtered record was - */
/*               |        failed.                                           */
/*               |        DEM_IRT_PENDING :                                 */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecord
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) resultValidateDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCheckDTCFormat;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( boolean, AUTOMATIC ) resultJudgeDTCClearTarget;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Specify the specified DTCFormat and check DTCFormat.*/
    resultOfCheckDTCFormat = Dem_CfgInfoPm_CheckDTCFormat( DTCFormat );

    /* Checks result of DTCFormat check. */
    if( resultOfCheckDTCFormat != DEM_IRT_OK )
    {
        /* Sets the return value to NG. */
        /* No Process. */
    }
    else
    {
        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

        /* Gets the event index of the fault record corresponding to the specific fault index. */
        resultOfGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( FaultIndex, &eventStrgIndex );

        /* Checks retained the event index of the fault record. */
        if( resultOfGetEventStrgIndex == DEM_IRT_OK )
        {
            /* Checks the event index range. */
            if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
            {
                /* The event index is within the range. */

                /* Checks event available status */
                availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );             /* [GUD]eventStrgIndex */

                if( availableStatus == (boolean)TRUE )
                {

                    resultJudgeDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );      /* [GUD]eventStrgIndex */

                    if( resultJudgeDTCClearTarget == (boolean)FALSE )
                    {
                        /* Gets the result of validation of DTC value. */
                        dtcValue    =   Dem_CfgInfoPm_GetUdsDTCValue( eventStrgIndex );             /* [GUD]eventStrgIndex */
                        resultValidateDTC = Dem_DataAvl_ValidateDTC( dtcValue );

                        /* Checks the result of validation of DTC value. */
                        if( resultValidateDTC == (boolean)TRUE )
                        {
                            /* DTC value is valid. */

                            /* Gets the fault record corresponding to the specific fault index. */
                            (void)Dem_DataMngC_GetFaultRecord( FaultIndex, &faultRecord ); /* no return check required */

                            /* Gets filtered record information for non-OBD corresponding to FreezeFrameList Index. */
                            retVal = Dem_Data_GetFilteredRecordInfo( eventStrgIndex, &faultRecord, ObdRecordNumberIndexPtr, RecordNumberIndexPtr, TSFFListIndexPtr, TSFFRecIndexPtr, DTCValuePtr, RecordNumberPtr );    /* [GUD]eventStrgIndex */
                        }
                        else
                        {
                            /* DTC value is invalid. */
                            /* Sets the return value to no data available. */
                            retVal = DEM_IRT_NODATAAVAILABLE;
                        }
                    }
                    else
                    {
                        retVal = DEM_IRT_NODATAAVAILABLE;
                    }
                }
                else
                {
                    /* event index is not available */
                    /* Sets the return value to no data available. */
                    retVal = DEM_IRT_NODATAAVAILABLE;
                }
            }
            else
            {
                /* The event index is out of the range. */
                /* No Process. */
            }
        }
        else
        {
            /* An exception error occurred by reading of the event index of the fault record. */
            /* Sets the return value to NG. */
            /* No Process. */
        }
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetFilteredRecordInfo                           */
/* Description   | Gets the filtered freeze frame record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in/out] ObdRecordNumberIndexPtr :                       */
/*               |        The index corresponding to the specified and nex- */
/*               |        t OBD record number.                              */
/*               | [in/out] RecordNumberIndexPtr :                          */
/*               |        The index corresponding to the specified and nex- */
/*               |        t record number.                                  */
/*               | [in/out] TSFFListIndexPtr :                              */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_PENDING :                                 */
/*               |                                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr, /* MISRA DEVIATION */
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /* Gets filtered record information for OBD corresponding to FreezeFrameList Index. */
    retVal = Dem_Data_GetObdFilteredRecordInfo( EventStrgIndex, FaultRecordPtr, ObdRecordNumberIndexPtr, DTCValuePtr, RecordNumberPtr );
    if( retVal == DEM_IRT_NODATAAVAILABLE )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    {
        /* No more filtered record information for OBD. */

        /* Gets filtered record information for non-OBD corresponding to FreezeFrameList Index. */
        retVal = Dem_Data_GetNonObdFilteredRecordInfo( EventStrgIndex, FaultRecordPtr, RecordNumberIndexPtr, TSFFListIndexPtr, TSFFRecIndexPtr, DTCValuePtr, RecordNumberPtr ); /* [GUDCHK:CALLER]EventStrgIndex */
    }

    /* Returns with the result. */
    return retVal;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetObdFilteredRecordInfo                        */
/* Description   | Gets the filtered freeze frame record for OBD.           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in/out] ObdRecordNumberIndexPtr :                       */
/*               |        The index corresponding to the specified and nex- */
/*               |        t OBD record number.                              */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) obdFreezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    /* Initializes the return value to No data available. */
    retVal = DEM_IRT_NODATAAVAILABLE;

    /* DTCAttribute table indicated by the DTCAttribute table list Index of the held DTC table is held. */
    Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass( EventStrgIndex, &obdFreezeFrameClassRef, &obdFreezeframeRecNumClassRef );    /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] obdFreezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] obdFreezeframeRecNumClassRef/EventStrgIndex */

    /* Checks the reference of freeze frame record number class. */
    if( obdFreezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                                        /* [GUD:if] obdFreezeframeRecNumClassRef */
    {
        /* Holds the FreezeFrameRecNumClass table pointed to by the FreezeFrameRecNumClass table list Index for OBD */
        /* of the held DTCAttribute table. */
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[obdFreezeframeRecNumClassRef];                             /* [GUD] obdFreezeframeRecNumClassRef */

        /* Gets an effective record number from specified record number Index */
        retVal = Dem_Data_GetObdFFRecNumByRecordNumberIndex( EventStrgIndex, DTCValuePtr, FaultRecordPtr, freezeFrameRecNumClassPtr, ObdRecordNumberIndexPtr, RecordNumberPtr );    /* [GUD]EventStrgIndex */
    }
    else
    {
        /* FreezeFrameRecordClass None */
        /* No Process. */
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_GetObdFFRecNumByRecordNumberIndex               */
/* Description   | Gets a record number of Freeze Frame by specifiend reco- */
/*               | rd number index.                                         */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The address of DemFreezeFrameRecNumClass table.   */
/*               | [in/out] ObdRecordNumberIndexPtr :                       */
/*               |        The index corresponding to the specified and nex- */
/*               |        t OBD record number.                              */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFFRecNumByRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;
    VAR( boolean, AUTOMATIC ) loopEnd;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retCheckOutputObdFFD;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */

    Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &obdFFRClassPerDTCMaxNum );
    obdFFDRecordNum = Dem_ObdFFDRecordNum;
    loopEnd =   (boolean)FALSE;

    for( recordNumberIndex = *ObdRecordNumberIndexPtr; recordNumberIndex < obdFFRClassPerDTCMaxNum; recordNumberIndex++ )   /* [GUD:for] recordNumberIndex */
    {
        /* Holds the DemFreezeFrameRecordIndex pointed to by the FreezeFrameRecNumClass table list Index */
        /* of the held FreezeFrameRecNumClass table.  */
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[recordNumberIndex];           /* [GUD] recordNumberIndex */

        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                      /* [GUD:if] freezeFrameRecordClassIndex */
        {
            /* Checks whether the OBD record number index array in FreezeFrameListRecord */
            /* pointed by the auto variable "recordNumberIndex" is invalid or not. */
            if( FaultRecordPtr->ObdRecordNumberIndex[recordNumberIndex] < obdFFDRecordNum )                                 /* [GUD] recordNumberIndex */
            {
                /* The index is valid. */

                /* DemFreezeFrameRecordNumber of the FreezeFrameRecordClass table stored */
                /* in the designated record number storage area is stored. */
                freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                  /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                *RecordNumberPtr = freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber;                                   /* [GUD] freezeFrameRecordClassPtr */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
                freezeFrameRecordTrigger  = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;                         /* [GUD] freezeFrameRecordClassPtr */
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                    /* [GUD:RET:TRUE] EventStrgIndex */
                if( misfireEventKind == (boolean)TRUE )
                {
                    retCheckOutputObdFFD = Dem_Misfire_CheckOutputFilteredObdFFD( EventStrgIndex, freezeFrameRecordTrigger, &misfireCylinderNumber );   /* [GUD]EventStrgIndex */
                    if( retCheckOutputObdFFD == (boolean)TRUE )
                    {
                        *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireCylinderNumber );
                        loopEnd =   (boolean)TRUE;
                    }
                }
                else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex */
                    /* pointed to by the Index next to the specified record number Index. */
                    *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );     /* [GUDCHK:CALLER]EventStrgIndex */
                    loopEnd =   (boolean)TRUE;
                }
            }
            else
            {
                /* The index is invalid. */
                /* Tries a next. */
                /* No Processing. */
            }
        }

        if ( loopEnd == (boolean)TRUE )
        {
            break;
        }
    }

    if( recordNumberIndex < obdFFRClassPerDTCMaxNum )
    {
        /* Stores the record number Index + 1 specified in the designated record number Index storage area. */
        *ObdRecordNumberIndexPtr = recordNumberIndex + (Dem_u08_FFListIndexType)1U;
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }
    else
    {
        *ObdRecordNumberIndexPtr = recordNumberIndex ;
        /* Sets the return value to no data avalable. */
        retVal = DEM_IRT_NODATAAVAILABLE;
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_GetNonObdFilteredRecordInfo                     */
/* Description   | Gets the filtered freeze frame record.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in/out] RecordNumberIndexPtr :                          */
/*               |        The index corresponding to the specified and nex- */
/*               |        t record number.                                  */
/*               | [in/out] TSFFListIndexPtr :                              */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_PENDING :                                 */
/*               |                                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetNonObdFilteredRecordInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,    /* MISRA DEVIATION */
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,              /* MISRA DEVIATION */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    /* Initializes the return value to No data available. */
    retVal = DEM_IRT_NODATAAVAILABLE;

    /* DTCAttribute table indicated by the DTCAttribute table list Index of the held DTC table is held. */
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef ); /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */

    /* Checks the reference of freeze frame record number class. */
    if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                               /* [GUD:if] freezeframeRecNumClassRef */
    {
        /* Holds the FreezeFrameRecNumClass table pointed to by the FreezeFrameRecNumClass table list Index */
        /* of the held DTCAttribute table. */
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ freezeframeRecNumClassRef ];                  /* [GUD] freezeframeRecNumClassRef */

        nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

        /* Check specified record number Index. */
        if( (Dem_u08_FFListIndexType)*RecordNumberIndexPtr < nonOBDFFRClassPerDTCMaxNum )
        {
            /* Gets an effective record number from specified record number Index */
            retVal = Dem_Data_GetFFRecNumByRecordNumberIndex( EventStrgIndex, DTCValuePtr, FaultRecordPtr, freezeFrameRecNumClassPtr, RecordNumberIndexPtr, RecordNumberPtr );  /* [GUDCHK:CALLER]EventStrgIndex */
        }
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
        else
        {
            /* Gets an effective record number from specified TimeSeriesFreezeFrameListIndex. */
            retVal = Dem_Data_GetFFRecNumByTSFFListIndex( EventStrgIndex, DTCValuePtr, FaultRecordPtr, TSFFListIndexPtr, TSFFRecIndexPtr, RecordNumberPtr );    /* [GUDCHK:CALLER]EventStrgIndex */
        }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

    }
    else
    {
        /* FreezeFrameRecordClass None */
        /* No Process. */
    }

    /* Returns with the result. */
    return retVal;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetFFRecNumByTSFFListIndex                      */
/* Description   | Gets a record number of Freeze Frame by specified time   */
/*               | series freeze frame list index.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in/out] TSFFListIndexPtr :                              */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_NG : Retrieving the filtered record was - */
/*               |        failed.                                           */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByTSFFListIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC) TSFFRecIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRecNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) startIndex;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    /* Initializes loopEnd to FALSE. */
    loopEnd = (boolean)FALSE;

    /* Initializes the resultOfGetTSFFRecNum value to NG. */
    resultOfGetTSFFRecNum = DEM_IRT_NG;

    /* Holds the specified time series freeze frame list index as search start index. */
    startIndex = (Dem_u08_TSFFListPerDTCIndexType)*TSFFListIndexPtr;

    /* there are no TimeSeriesFreezeFrameListIndex, sets the return value to no data available. */
    retVal = DEM_IRT_NODATAAVAILABLE;

    /* Repeat processing from a search start index to tsffRecordClassNumPerDTCMaxNum. */
    for( tsFFListIndex = startIndex; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ )      /* [GUD:for]tsFFListIndex */
    {
        /* Holds the time series freeze frame list index in the time series freeze frame record which */
        /* current time series freeze frame list index points at in freeze frame list record index. */
        tsFFListRecIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsFFListIndex];                   /* [GUD]tsFFListIndex */

        /* Checks whether the time series freeze frame list record index is not an invalid value. */
        if( tsFFListRecIndex < tsffTotalDTCNum )                                                            /* [GUD:if]tsFFListRecIndex */
        {
            /* Gets effective freeze frame record number by the time series freeze frame list record index. */
            resultOfGetTSFFRecNum = Dem_Data_GetFFRecNumByTSFFListRecIndex( EventStrgIndex, DTCValuePtr, tsFFListRecIndex, tsFFListIndex, TSFFRecIndexPtr, RecordNumberPtr );       /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD]tsFFListRecIndex *//* [GUD]tsFFListIndex */

            /* Checks the result of retrieving the freeze frame record number. */
            if( resultOfGetTSFFRecNum == DEM_IRT_OK )
            {
                /* Sets TRUE in loopEnd */
                loopEnd = (boolean)TRUE;
            }
            else if( resultOfGetTSFFRecNum == DEM_IRT_NODATAAVAILABLE )
            {
                /* An effective record number was not provided. */
                *TSFFRecIndexPtr = Dem_TSFFTotalTimeseriesFFRecordNum;
            }
            else
            {
                /* Other results are abnormal return values. */
                /* Sets TRUE in loopEnd */
                loopEnd = (boolean)TRUE;
            }
        }
        else
        {
            /* No Processing. */
        }

        /* Checks whether loopEnd is TRUE. */
        if( loopEnd == (boolean)TRUE )
        {
            /* Stores The time series freeze frame list index in out parameter. */
            *TSFFListIndexPtr = tsFFListIndex;

            /* Checks the result of retrieving the freeze frame record number at the time of the loop end. */
            if( resultOfGetTSFFRecNum == DEM_IRT_OK )
            {
                /* Updates the time series freeze frame list index and the time series freeze frame record index */
                Dem_Data_UpdateIndexForSearchTSFFRecNum( tsFFListRecIndex, TSFFListIndexPtr, TSFFRecIndexPtr );     /* [GUD]tsFFListRecIndex */
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* Other results just sets it in a function return value. */
                retVal = resultOfGetTSFFRecNum;
            }
            break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetFFRecNumByTSFFListRecIndex                   */
/* Description   | Gets a record number of Freeze Frame by specified time   */
/*               | series freeze frame list record index.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [in] TSFFListRecIndex :                                  */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] TSFFListIndex :                                     */
/*               |                                                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NODATAAVAILABLE : Available data were n - */
/*               |        ot provided.                                      */
/*               |        DEM_IRT_NG : Retrieving the filtered record was - */
/*               |        failed.                                           */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByTSFFListRecIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,           /* [PRMCHK:CALLER] */
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFStartRecNum;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recNumOffset;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) startIndex;
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) tsFFRecord;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) outputRecordNumber;
    VAR( boolean, AUTOMATIC ) retCheckOutputFFD;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */

    /* Initializes the return value to No Data Available. */
    retVal = DEM_IRT_NODATAAVAILABLE;

    /* Initializes loopEnd to FALSE. */
    loopEnd = (boolean)FALSE;

    /* Find a search start index from the time series freeze frame list record index and the time series freeze frame record index. */
    startIndex = Dem_Data_GetStartIndexOfTSFFRecord( TSFFListRecIndex, (*TSFFRecIndexPtr) );                                                /* [GUDCHK:CALLER]TSFFListRecIndex */

    /* Repeats loop processing from a search start index to the value that added 1 to an end index in the time series freeze frame table list. */
    for( tsFFRecIndex = startIndex; tsFFRecIndex <= ( Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemEndIndex ); tsFFRecIndex++ )      /* [GUDCHK:CALLER]TSFFListRecIndex *//* [GUD:for]tsFFRecIndex */
    {
        /* Gets the time series freeze frame record by current time series freeze frame record index. */
        resultOfGetTSFFRec = Dem_DataMngC_GetTimeSeriesFreezeFrameRecord( tsFFRecIndex, &tsFFRecord );                                      /* [GUD]tsFFRecIndex */

        /* Checks the result of retrieving the time series freeze frame record. */
        if( resultOfGetTSFFRec == DEM_IRT_OK )
        {
            /* Checks RecordStatus which a member of the time series freeze frame record. */
            if( tsFFRecord.RecordStatus == DEM_FFD_STORED )
            {
                /* Initializes start record number to 0. */
                startingRecordNumber = 0U;

                /* Gets the starting record number from TimeSeriesFreezeFrameRecordClassTable by */
                /* the fault index of the time series freeze frame record and the specified index of time-series freeze frame list index  */
                resultOfGetTSFFStartRecNum = Dem_Data_GetTSFFStartRecordNumber( EventStrgIndex, TSFFListIndex, &startingRecordNumber, &freezeFrameRecordTrigger );  /* [GUDCHK:CALLER]TSFFListIndex *//* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

                /* Checks the result of retrieving the starting record number. */
                if( resultOfGetTSFFStartRecNum == DEM_IRT_OK )
                {
                    /*  set configured DTC.     */
                    *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );     /* [GUD]EventStrgIndex */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */

                    outputRecordNumber  =   (boolean)FALSE;
                    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );    /* [GUD]EventStrgIndex */
                    if( misfireEventKind == (boolean)TRUE )
                    {
                        retCheckOutputFFD = Dem_Misfire_CheckOutputFilteredFFD( EventStrgIndex, freezeFrameRecordTrigger, &misfireCylinderNumber ); /* [GUD]EventStrgIndex */
                        if( retCheckOutputFFD == (boolean)TRUE )
                        {
                            /*  set cylinder DTC.           */
                            *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireCylinderNumber );
                            outputRecordNumber  =   (boolean)TRUE;
                        }
                    }
                    else
                    {
                        outputRecordNumber  =   (boolean)TRUE;
                    }

                    if ( outputRecordNumber == (boolean)TRUE )
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */
                    {
                        /* Subtract a start index of TimeSeriesFreezeFrameTable from the time series freeze frame record index */
                        /* and calculate the offset of the record number. */
                        recNumOffset = (Dem_u08_FFRecordNumberType)( tsFFRecIndex - Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemStartIndex );   /* [GUDCHK:CALLER]TSFFListRecIndex */

                        /* Stores the value that added offset of the record number that I calculated to DemStartingRecordNumber */
                        /* in TimeSeriesFreezeFrameRecordClassTable which the time series freeze frame list index points at in an out parameter. */
                        *RecordNumberPtr = startingRecordNumber + recNumOffset;

                        /* Sets the return value to OK. */
                        retVal = DEM_IRT_OK;
                    }
                }
                else
                {
                    /* Sets the return value to NG. */
                    retVal = DEM_IRT_NG;
                }

                /* Sets TRUE in loopEnd */
                loopEnd = (boolean)TRUE;
            }
            else
            {
                /* No Processing. */
            }
        }
        else
        {
            /* Sets TRUE in loopEnd. */
            loopEnd = (boolean)TRUE;

            /* Sets the return value to NG. */
            retVal = DEM_IRT_NG;
        }

        /* Checks whether loopEnd is TRUE. */
        if( loopEnd == (boolean)TRUE )
        {
            *TSFFRecIndexPtr = tsFFRecIndex;
            break;
        }
        else
        {
            /* No Processing. */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetStartIndexOfTSFFRecord                       */
/* Description   | Gets a search start index from the time series freeze f- */
/*               | rame list record index and the time series freeze frame  */
/*               | record index.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] TSFFListRecIndex :                                  */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] TSFFRecIndex :                                      */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/* Return Value  | Dem_u16_TSFFDIndexType                                   */
/*               |        startIndex                                        */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_TSFFDIndexType, DEM_CODE ) Dem_Data_GetStartIndexOfTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TSFFRecIndex
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) retVal;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;

    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    /* Checks whether the time series freeze frame record index is tsffTotalTimeseriesFFRecordNum. */
    if( TSFFRecIndex == tsffTotalTimeseriesFFRecordNum )
    {
        /* Sets DemStartIndex in TimeSeriesFreezeFrameTable */
        /* which the time series freeze frame list record index points at in a function return value. */
        retVal = Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemStartIndex;        /* [GUDCHK:CALLER]TSFFListRecIndex */
    }
    else
    {
        /* Sets the time series freeze frame record index in a function return value. */
        retVal = TSFFRecIndex;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetTSFFStartRecordNumber                        */
/* Description   | Update of the index information in conjunction with the  */
/*               | record number search of the time series freeze frame re- */
/*               | cord.                                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex :                                        */
/*               |        The index of corresponding to fault record list.  */
/*               | [in] TSFFListIndex :                                     */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [out] StartingRecordNumberPtr :                          */
/*               |        The Starting record number to be granted.         */
/*               | [out] FreezeFrameRecordTriggerPtr :                      */
/*               |        The DemFreezeFrameRecordTrigger retrieved.        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Update of the index information suc- */
/*               |        ceeded.                                           */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_NODATAAVAILABLE : Not Output Tarteg MIsf- */
/*               |        ire freeze frame record.                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFStartRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    /* Retains the DTC attributes table corresponding to the DTC attributes Index in the specified DTC table. */
    dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr *//* [GUD:RET:Not NULL_PTR] EventStrgIndex */

    if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
    {
        /* Retains the reference of time-series freeze frame record class corresponding to the spcecified DTC attributes table */
        /* which indicated by the specified time-series freeze frame list index. */
        tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[TSFFListIndex];    /* [GUD]dtcAttributePtr *//* [GUDCHK:CALLER]TSFFListIndex */

        /* Evaluates whether the retained reference of time-series freeze frame record class means valid.  */
        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                      /* [GUD:if]tsFFRecClassRef */
        {
            /* Stores the starting record number of time-series freeze frame record class which pointed by the specified reference the class. */
            *StartingRecordNumberPtr = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStartingRecordNumber;               /* [GUD]tsFFRecClassRef */
            *FreezeFrameRecordTriggerPtr = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;   /* [GUD]tsFFRecClassRef */

            /* Sets the return value to OK. */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process. */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_UpdateIndexForSearchTSFFRecNum                  */
/* Description   | Update of the index information in conjunction with the  */
/*               | record number search of the time series freeze frame re- */
/*               | cord.                                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] TSFFListRecIndex :                                  */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in/out] TSFFListIndexPtr :                              */
/*               |        The Index of TimeSeriesFreezeFrameList correspon- */
/*               |        ding to the fault index.                          */
/*               | [in/out] TSFFRecIndexPtr :                               */
/*               |        The Index of TimeSeriesFreezeFrame record corres- */
/*               |        ponding to the fault index.                       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_UpdateIndexForSearchTSFFRecNum
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,       /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr
)
{
    /* Checks whether a value of the the time series freeze frame record index is less than DemEndIndex */
    /* in TimeSeriesFreezeFrameTable which TSFFListRecIndex points at. */
    if( (Dem_u16_TSFFDIndexType)*TSFFRecIndexPtr < Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemEndIndex )   /* [GUDCHK:CALLER]TSFFListRecIndex */
    {
        /* Stores the value that added 1 to the time series freeze frame record index in an out parameter. */
        *TSFFRecIndexPtr += (Dem_u16_TSFFDIndexType)1U;
    }
    else
    {
        /* Stores the value that added 1 to the time series freeze frame list index in an out parameter. */
        *TSFFListIndexPtr = *TSFFListIndexPtr + (Dem_u08_TSFFListPerDTCIndexType)1U;

        /* Stores DemTSFFTotalTimeseriesFFRecordNum in an out parameter. */
        *TSFFRecIndexPtr = Dem_TSFFTotalTimeseriesFFRecordNum;
    }

    return;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_GetFFRecNumByRecordNumberIndex                  */
/* Description   | Gets a record number of Freeze Frame by specifiend reco- */
/*               | rd number index.                                         */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [out] DTCValuePtr :                                      */
/*               |        The DTC value retrieved.                          */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record to get a filterd record.         */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The address of DemFreezeFrameRecNumClass table.   */
/*               | [in/out] RecordNumberIndexPtr :                          */
/*               |        The index corresponding to the specified and nex- */
/*               |        t record number.                                  */
/*               | [out] RecordNumberPtr :                                  */
/*               |        The record number retrieved.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the filtered record was - */
/*               |        successful.                                       */
/*               |        DEM_IRT_PENDING :                                 */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecNumByRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( boolean, AUTOMATIC ) loopEnd;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckOutputFFD;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;

    Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    loopEnd =   (boolean)FALSE;

    for( recordNumberIndex = *RecordNumberIndexPtr; recordNumberIndex < nonOBDFFRClassPerDTCMaxNum; recordNumberIndex++ )   /* [GUD:for] recordNumberIndex */
    {
        /* Holds the DemFreezeFrameRecordIndex pointed to by the FreezeFrameRecNumClass table list Index */
        /* of the held FreezeFrameRecNumClass table.  */
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[recordNumberIndex];           /* [GUD] recordNumberIndex */

        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                      /* [GUD:if] freezeFrameRecordClassIndex */
        {
            /* Checks whether the record number index array in FreezeFrameListRecord */
            /* pointed by the auto variable "recordNumberIndex" is invalid or not. */
            if( FaultRecordPtr->RecordNumberIndex[recordNumberIndex] < nonObdFFDRecordNum )                                 /* [GUD] recordNumberIndex */
            {
                /* The index is valid. */

                /* DemFreezeFrameRecordNumber of the FreezeFrameRecordClass table stored */
                /* in the designated record number storage area is stored. */
                freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                  /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                *RecordNumberPtr = freezeFrameRecordClassPtr->DemFreezeFrameRecordNumber;                                   /* [GUD] freezeFrameRecordClassPtr */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )      /*  [FuncSw]    */
                freezeFrameRecordTrigger  = freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger;
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );        /* [GUD:RET:TRUE] EventStrgIndex */
                if( misfireEventKind == (boolean)TRUE )
                {
                    retCheckOutputFFD = Dem_Misfire_CheckOutputFilteredFFD( EventStrgIndex, freezeFrameRecordTrigger, &misfireCylinderNumber ); /* [GUD]EventStrgIndex */
                    if( retCheckOutputFFD == (boolean)TRUE )
                    {
                        *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( misfireCylinderNumber );
                        loopEnd      =  (boolean)TRUE;
                    }
                }
                else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )               */
                {
                    /* Holds the FreezeFrameRecordClass table pointed to by DemFreezeFrameRecordIndex */
                    /* pointed to by the Index next to the specified record number Index. */
                    *DTCValuePtr =  Dem_CfgInfoPm_GetUdsDTCValue( EventStrgIndex );     /* [GUDCHK:CALLER]EventStrgIndex */
                    loopEnd =   (boolean)TRUE;
                }
            }
            else
            {
                /* The index is invalid. */
                /* Tries a next. */
                /* No Processing. */
            }
        }
        if ( loopEnd == (boolean)TRUE )
        {
            break;
        }
    }

    if( recordNumberIndex < nonOBDFFRClassPerDTCMaxNum )
    {
        /* Stores the record number Index + 1 specified in the designated record number Index storage area. */
        *RecordNumberIndexPtr = recordNumberIndex + (Dem_u08_FFListIndexType)1U;
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }
    else
    {
        *RecordNumberIndexPtr = recordNumberIndex ;
        /* Sets the return value to pending. */
        retVal = DEM_IRT_PENDING;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
