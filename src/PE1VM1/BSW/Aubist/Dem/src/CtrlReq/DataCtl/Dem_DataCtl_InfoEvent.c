/* Dem_DataCtl_InfoEvent_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_InfoEvent/CODE                                */
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
#include "../../../inc/Dem_Pm_DataCtl.h"
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
/* Function Name | Dem_Data_GetDTCStatus                                    */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) result;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    /* Gets the status of DTC of the event record corresponding to the specified event index. */
    result = Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

    /* Checks the result of retrieving the event record. */
    if( result == DEM_IRT_OK )
    {
        /* Retrieving the event record is successful. */

        /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
        *DTCStatusPtr = statusOfDTC;
    }
    else
    {
        /* Retrieving the event record is failed. */

        /* Sets result of retrievng the event record to the return value. */
        retVal = result;
    }

    /* Returns with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetNumberOfEventMemoryEntries                   */
/* Description   | Gets the number of event memory entries corresponding t- */
/*               | he specified the DTCOrigin.                              */
/* Preconditions | Consistency of the specified DTCOrigin has been already  */
/*               |  checked.                                                */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        DTCOrigin type of Dem's external definition.      */
/*               | [out] NumberOfEventMemoryEntriesPtr :                    */
/*               |        The number of event memory entries.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Retrieving the number of event memo- */
/*               |        ry entries was successful.                        */
/*               |        DEM_IRT_NG : Retrieving the number of event memo- */
/*               |        ry entries was failed.                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    /* Checks DTCOrigin type */
    if( DTCOrigin == (Dem_DTCOriginType)DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        /* Starts exclusion. */
        SchM_Enter_Dem_EventMemory();

        /* Gets the event memory record of primary memory. */
        Dem_DataMngC_GetEventMemoryRecord( &eventMemoryRecord );

        /* Finishes exclusion. */
        SchM_Exit_Dem_EventMemory();

        /* Stores the acquired NumberOfEventMemoryEntries. */
        *NumberOfEventMemoryEntriesPtr = eventMemoryRecord.NumberOfEventMemoryEntries;
    }
    else
    {
        /* DTCOrigin type does not match. */

        /* Sets the return value to NG. */
        retVal = DEM_IRT_NG;
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
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
