/* Dem_DataCtl_EventEntry02Make_Event_c(v5-3-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry02Make_Event/CODE                   */
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
/* Function Name | Dem_UdmData_SetDTCStatusToTmp                            */
/* Description   | Sets the specified value to the UDS DTC status byte in - */
/*               | event memory entry of temporary area.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus :                                         */
/*               |        The UDS DTC status byte which will set.           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetDTCStatusToTmp
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    /* Sets the specified DTCStatus to StatusOfDTC of the event memory entry of temporary area. */
    Dem_UdmTmpEventMemoryEntry.EventRecord.StatusOfDTC       = DTCStatus;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GetDTCStatusFromTmp                          */
/* Description   | Gets the UDS DTC status byte from the event memory entr- */
/*               | y of temporary area.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved. */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusFromTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr       =   Dem_UdmTmpEventMemoryEntry.EventRecord.StatusOfDTC;

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
