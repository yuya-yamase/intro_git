/* Dem_UdmDataCtl_EventEntry03Compare_c(v5-3-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry03Compare/CODE                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"


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
/* Function Name | Dem_UdmData_CompareEventMemoryEntryToTmp                 */
/* Description   | Compares the event memory entry to temporary area corre- */
/*               | sponding to the event index of temporary area.           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_CompareEventMemoryEntryToTmp
( void )
{
    /* Compares the event memory entry corresponding to the saved event index to the temporary area. */

    Dem_UdmData_CompareEventRecordToTmp();

    Dem_UdmData_CompareFaultRecordToTmp();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CompareEventRecordToTmp                      */
/* Description   | Compares the event record corresponding to the temoprary */
/*               | event meomry entry.                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_CompareEventRecordToTmp
( void )
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    if( Dem_UdmTmpEventMemoryEntry.UdmEventIndex < eventConfigureNum )
    {
        /* compare with record data. */
        Dem_UdmTmpEventMemoryEntry.ResultOfComparingEventRecords = Dem_UdmEventMngC_CompareEventRecord( Dem_UdmTmpEventMemoryEntry.UdmEventIndex, &Dem_UdmTmpEventMemoryEntry.EventRecord );
    }
    else
    {
        Dem_UdmTmpEventMemoryEntry.ResultOfComparingEventRecords = DEM_IRT_OK;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CompareFaultRecordToTmp                      */
/* Description   | Compares the fault record corresponding to the temoprary */
/*               | event meomry entry.                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_CompareFaultRecordToTmp
( void )
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) failRecordNum;

    failRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex );

    if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex < failRecordNum )
    {
        /* compare with record data. */
        Dem_UdmTmpEventMemoryEntry.ResultOfComparingFaultRecords = Dem_UdmFaultMngC_CompareFaultRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpEventMemoryEntry.FaultRecord );
    }
    else
    {
        Dem_UdmTmpEventMemoryEntry.ResultOfComparingFaultRecords = DEM_IRT_OK;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetResultOfCmpFFRecordToTmp                  */
/* Description   | Set the comparison result of freeze frame record in-     */
/*               | temoprary                                                */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] Result:                                             */
/*               |        DEM_IRT_OK                                        */
/*               |        DEM_IRT_NG                                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetResultOfCmpFFRecordToTmp
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    Dem_UdmTmpEventMemoryEntry.ResultOfComparingFFRecords = Result;

    return;
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
