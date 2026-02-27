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
/* Saved temporary area of event memory entry */
typedef struct {
    Dem_UdmEventRecordForCtlType        EventRecord;
    Dem_UdmFaultRecordType              FaultRecord;
    Dem_UdmFreezeFrameRecordForCtlType  FreezeFrameRecord;
    Dem_UdmEventMemoryRecordType        EventMemoryRecord;
    Dem_u16_UdmEventIndexType           UdmEventIndex;
    Dem_u16_UdmFFDIndexType             OldestFreezeFrameRecordIndex;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
    Dem_u16_TSFFListIndexType           TSFFListCurrenctIndex;
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */
    Dem_u16_UdmDemMemKindIndexType      UdmGroupKindIndex;
    Dem_u08_OrderIndexType              BeforeNumberOfEventMemoryEntries;
    Dem_u08_InternalReturnType          ResultOfComparingEventRecords;
    Dem_u08_InternalReturnType          ResultOfComparingFaultRecords;
    Dem_u08_InternalReturnType          ResultOfComparingFFRecords;
    boolean                             StorageOfFFDAtFirstTimeFlag;
} Dem_UserDefMemTmpEventMemoryEntryType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry          */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry00Init    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpMemoryWithoutRecord
( void );

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry01Latch   */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry02Make  */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry03Compare */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_CompareEventMemoryEntryToTmp
( void );

FUNC( void, DEM_CODE ) Dem_UdmData_CompareEventRecordToTmp
( void );

FUNC( void, DEM_CODE ) Dem_UdmData_CompareFaultRecordToTmp
( void );
FUNC( void, DEM_CODE ) Dem_UdmData_SetResultOfCmpFFRecordToTmp
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry04Regist  */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventOverwitten
(
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAtOverwritten
);
FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryEntryFromTmp
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
);

/*-----------------------------------------*/
/*  Dem_UdmDataCtl_EventEntry02Clear.c     */
/*-----------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( void, DEM_CODE ) Dem_UdmData_ClearFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
);

FUNC( void, DEM_CODE ) Dem_UdmData_ClearFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, AUTOMATIC ) UdmEventMemoryRecordPtr
);

FUNC( void, DEM_CODE ) Dem_UdmData_SubtractOneFromNumOfEventMemoryEntries
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, AUTOMATIC ) UdmEventMemoryRecordPtr
);

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
extern VAR( Dem_UserDefMemTmpEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_UdmTmpEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#endif /* DEM_DATACTL_EVENTENTRY_local_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
