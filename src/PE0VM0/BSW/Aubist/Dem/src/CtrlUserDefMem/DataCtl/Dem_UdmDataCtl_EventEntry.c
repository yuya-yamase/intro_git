/* Dem_UdmDataCtl_EventeEntry_c(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventeEntry/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"
#include "Dem_UdmDataCtl_local.h"

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

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/

VAR( Dem_UserDefMemTmpEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_UdmTmpEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmData_SaveEventMemoryEntryToTmp                    */
/* Description   | Saves an event memory entry specified by event index to  */
/*               |  temporary area.                                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Saves the event memory entry corresponding to the specified event ID. */
    retVal = Dem_UdmData_SaveEventMemoryEntry( UdmEventIndex );

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_UpdateEventMemoryEntryFromTmp                */
/* Description   | Updates the event memory entry from temporary area.      */
/* Preconditions | None                                                     */
/*               | [in]  FaultRecordOverwriteFlag                           */
/*               |              FALSE : overwrite isn't occurred.           */
/*               |              TRUE  : overwrite occurred.                 */
/*               | [in]  UdmEventIndexOverwritten                           */
/*               |              overwritten event.                          */
/*               | [in]  DTCStatusAtOverwritten                             */
/*               |              statusOfDTC of overwritten event.           */
/*               | [in]  TSFFListIndexOverwritten                           */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_UpdateEventMemoryEntryFromTmp
(
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAtOverwritten,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
)
{
    Dem_UdmData_StoreEventOverwitten( FaultRecordOverwriteFlag, UdmEventIndexOverwritten, DTCStatusAtOverwritten );

    /* Compares the event memory entry corresponding to the event index of temporary area from temporary area. */
    Dem_UdmData_CompareEventMemoryEntryToTmp();

    /* Stores the event memory entry from the event memory entry of temporary area. */
    Dem_UdmData_StoreEventMemoryEntryFromTmp( TSFFListIndexOverwritten );

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

