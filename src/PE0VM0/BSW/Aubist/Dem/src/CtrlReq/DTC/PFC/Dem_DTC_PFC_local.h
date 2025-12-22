/* Dem_DTC_PFC_local_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_LOCAL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DTC_PFC_LOCAL_H
#define DEM_DTC_PFC_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#define DEM_PFC_RECORD_ENOUGH_EMPTY_SPACE_NUM ((Dem_u08_PFCIndexType)2U)
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCRecordByOrder
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFC_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
);

/*  Dem_DTC_PFC_StoreRecord.c   */
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCRecordWithQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
);
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCRecordWithClearCondition
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckRegistPFCRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);


/*  Dem_DTC_PFC_UpdateOrder_Pattern.c   */
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_DTC_GetUpdateOrderMaxCount
( void );
FUNC( void, DEM_CODE ) Dem_DTC_GetUpdateOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
);

#endif  /* ( DEM_PFC_SUPPORT == STD_OFF )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif  /* DEM_DTC_PFC_LOCAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

