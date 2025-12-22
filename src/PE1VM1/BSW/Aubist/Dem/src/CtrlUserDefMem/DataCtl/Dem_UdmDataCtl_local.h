/* Dem_UdmDataCtl_local_h(v5-7-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_local/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UDMDATACTL_LOCAL_H
#define DEM_UDMDATACTL_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*  if added member in Dem_UdmTmpRecordNumberByDTCType, add copy job in Dem_UdmDataCtl_CopyTmpRecordNumberByDTCWithoutRecordNumber().   */
typedef struct
{
    Dem_u32_UdmOccurrenceOrderType      OccurrenceOrder;
    Dem_u16_AllFFDIndexType             FreezeFrameDataIndex;
    Dem_u16_TSFFListIndexType           TimeSeriesFreezeFrameListIndex;
    Dem_u08_ConsistencyIdType           CidUdmFreezeFrameRecords;
    Dem_u08_FFRecordNumberType          RecordNumber;
    Dem_u08_FreezeFrameDataType         FreezeFrameDataType;
    Dem_u08_FFStoredStatusType          RecordStatus;
} Dem_UdmTmpRecordNumberByDTCType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/*-----------------------------------------*/
/*  Dem_UdmDataCtl_DisableDTCInfo.c        */
/*-----------------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckAndGetConsistentFFRecord
(
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpRecordNumberByDTCPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) UdmFreezeFrameRecordPtr
);

/*-----------------------------------------*/
/*  Dem_UdmDataCtl_InfoFFD_Sort.c          */
/*-----------------------------------------*/
FUNC( void, DEM_CODE ) Dem_UdmData_SortSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);

/*-----------------------------------------*/
/*  Dem_UdmDataCtl_InfoFFD.c               */
/*-----------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllFFRecordNumber
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    VAR( uint8, AUTOMATIC ) TotalLengthOfBuffer,
    VAR( uint8, AUTOMATIC ) OffsetPosOfBuffer,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
);

/*-----------------------------------------*/
/*  Dem_UdmDataCtl_InfoFFD.c               */
/*-----------------------------------------*/
FUNC( Dem_u16_FFRecNumStoredIndexType, DEM_CODE ) Dem_UdmData_GetStoredRecordNumberCounts
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_UdmTmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_UdmTmpRecordNumberByDTC[DEM_UDM_MAX_NUMBER_FF_PER_DTC];


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#endif /* DEM_UDMDATACTL_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
