/* Dem_Control_FilteredRecord_c(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FilteredRecord/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_FFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "Dem_Control_local.h"

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

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_SetFreezeFrameRecordFilter                   */
/* Description   | Sets freeze frame record filter according to the specif- */
/*               | ied conditions.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls               */
/*               | [out] NumberOfFilteredRecordsPtr :                       */
/*               |        Number of freeze frame records currently stored - */
/*               |        in the event memory                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : wrong filter.                        */
/*               |        DEM_IRT_WRONG_CONDITION : Wrong condition         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetFreezeFrameRecordFilter
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_WRONG_CONDITION;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_EventMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_EventMemory();

        retVal  =   Dem_FFD_SetFreezeFrameRecordFilter( DTCFormat, NumberOfFilteredRecordsPtr );
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetNextFilteredRecord                        */
/* Description   | Gets the next filtered freeze frame record which match - */
/*               | the filter criteria.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        hefilter returned by this function                */
/*               | [out] RecordNumberPtr :                                  */
/*               |        Freeze frame record number of the reported DTC    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later. Only used by asynchr- */
/*               |        onous interfaces.                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredRecord
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_EventMemoryUpdateStatusType, AUTOMATIC ) eventMemoryUpdatingStatus;

    eventMemoryUpdatingStatus = Dem_Data_GetEventMemoryUpdatingStatus();

    if ( eventMemoryUpdatingStatus == DEM_EVENT_MEMORY_UPDATING )
    {
        (*DTCValuePtr)     = DEM_DTC_VALUE_MIN;
        (*RecordNumberPtr) = DEM_FFD_RECORD_NUMBER_MIN;
        retVal = DEM_IRT_PENDING;
    }
    else
    {
        SchM_Enter_Dem_EventMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_EventMemory();

        retVal = Dem_FFD_GetNextFilteredRecord( DTCValuePtr, RecordNumberPtr );
    }


    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
