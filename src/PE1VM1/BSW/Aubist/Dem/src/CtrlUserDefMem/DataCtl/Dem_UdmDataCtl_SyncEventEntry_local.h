/* Dem_UdmDataCtl_EventEntry_local_h(v5-5-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry_local/HEADER                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDMDATACTL_EVENTENTRY_local_H
#define DEM_UDMDATACTL_EVENTENTRY_local_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "Dem_UdmDataCtl_local.h"
#include "../../../inc/Dem_Rc_UdmMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/

/* Saved temporary area of sync event memory entry */
typedef struct {
    Dem_UdmEventRecordForCtlType        EventRecord;
    Dem_UdmFaultRecordType              FaultRecord;
    Dem_UdmFFRMngInfoType               FFRMngInfo;
    Dem_UdmEventMemoryRecordType        EventMemoryRecord;
    Dem_u16_UdmEventIndexType           UdmEventIndex;
    Dem_u16_UdmFFDIndexType             OldestFreezeFrameRecordIndex;
    Dem_u16_UdmDemMemKindIndexType      UdmGroupKindIndex;
    Dem_u08_OrderIndexType              BeforeNumberOfEventMemoryEntries;
    Dem_u08_InternalReturnType          ResultOfComparingEventRecords;
    Dem_u08_InternalReturnType          ResultOfComparingFaultRecords;
    boolean                             StorageOfFFDAtFirstTimeFlag;
} Dem_UserDefMemTmpSyncEventMemoryEntryType;


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



#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#endif /* DEM_DATACTL_EVENTENTRY_local_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
