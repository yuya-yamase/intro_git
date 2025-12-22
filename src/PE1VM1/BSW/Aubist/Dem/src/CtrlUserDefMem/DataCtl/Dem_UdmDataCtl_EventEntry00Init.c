/* Dem_UdmDataCtl_EventEntry00Init_c(v5-5-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry00Init/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Utl.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"

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
/* Function Name | Dem_UdmData_InitTmpEventMemoryEntry                      */
/* Description   | Initializes event memory entry of temporary area.        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpEventMemoryEntry
( void )
{
    /* Initializes the event record. */
    Dem_UdmEventMngC_InitRecord( &Dem_UdmTmpEventMemoryEntry.EventRecord );
    /* Initializes the fault record. */
    Dem_UdmFaultMng_InitCtlRecordData( &Dem_UdmTmpEventMemoryEntry.FaultRecord );

    /* Initializes the specific freeze frame record. */
    Dem_UdmFFDMngC_InitFreezeFrameRecordData( &Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord );

    /* Initializes the event memory record list. */
    Dem_UdmEventMngC_InitEvtMemRecData( &Dem_UdmTmpEventMemoryEntry.EventMemoryRecord );

    /* Initializes the event index. */
    Dem_UdmData_InitTmpMemoryWithoutRecord();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_InitTmpMemoryWithoutRecord                   */
/* Description   | Initialization of temporary event memory entries.        */
/*               | (excluding records)                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpMemoryWithoutRecord
( void )
{
    /* Initializes UserDefMem event Table index. */
    Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex = DEM_UDMTABLEINDEX_INVALID;

    /* Initializes the event index. */
    Dem_UdmTmpEventMemoryEntry.UdmEventIndex = DEM_UDMEVENTINDEX_INVALID;

    /* Initializes the oldest freeze frame record index. */
    Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )    /* [FuncSw]   */
    /* Initializes the current index for time-series freeze frame list record list. */
    Dem_UdmTmpEventMemoryEntry.TSFFListCurrenctIndex = DEM_TSFFLISTINDEX_INVALID;
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */

    /* Initializes the number of event memory entries before being updated. */
    Dem_UdmTmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries = DEM_NUMOFEVTMEMENT_INITIAL;

    /* Initializes the result of comparing each records with no differences. */
    Dem_UdmTmpEventMemoryEntry.ResultOfComparingEventRecords  = DEM_IRT_OK;
    Dem_UdmTmpEventMemoryEntry.ResultOfComparingFaultRecords  = DEM_IRT_OK;

    /* Initializes the result of comparing freeze frame records with no differences. */
    Dem_UdmTmpEventMemoryEntry.ResultOfComparingFFRecords = DEM_IRT_OK;

    /* Initializes the flag for storage of FFD at first time. */
    Dem_UdmTmpEventMemoryEntry.StorageOfFFDAtFirstTimeFlag  = (boolean)FALSE;

    return;
}



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
