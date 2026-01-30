/* Dem_DataCtl_FilteredRecord_c(v5-8-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetNumberOfFilteredRecords
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    /* Stores NumberOfFilteredRecords. */
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();
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
/*               | [in/out] FilteredRecordSearchInfoPtr :               */
/*               |        Pointer to Dem_FilteredRecordSearchInfo.          */
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
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecord
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_FilteredRecordSearchInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FilteredRecordSearchInfoPtr,
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
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
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
        faultIndex = FilteredRecordSearchInfoPtr->FaultIndex;

        /* Gets the event index of the fault record corresponding to the specific fault index. */
        resultOfGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );

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
                             retVal = Dem_Data_GetFilteredRecordSub( faultIndex, eventStrgIndex, dtcValue, FilteredRecordSearchInfoPtr, DTCValuePtr, RecordNumberPtr );
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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
