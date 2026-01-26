/* Dem_Pm_DataCtl_OBD_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DataCtl_OBD/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_DATACTL_OBD_H
#define DEM_PM_DATACTL_OBD_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_Data_GetFaultOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) FaultOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
);

#if ( DEM_PID_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_Data_GetNumberOfOBDDTCByDTCStatus_forPIDDataA
(
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC ) NumberOfConfirmedPtr,
    P2VAR( Dem_u16_EventNumType, AUTOMATIC, AUTOMATIC ) NumberOfMILPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveCDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr
);
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */

#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
FUNC( boolean, DEM_CODE ) Dem_Data_GetMILStatus_NormalEvent
( void );
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_GetPendingOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) FaultOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_GetConfirmedOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) ConfirmedOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckStoredOBDFFDInFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

#endif  /* ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_GetMILOrderEventStrgIndex
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) MILOrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OrderExistPtr
);
#endif /* (DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

#if ( DEM_INDICATOR_USE == STD_ON )
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_ClearMILOccurrenceOrderInfo
( void );
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    */
#endif  /* ( DEM_INDICATOR_USE == STD_ON )    */

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataCtl_SearchPriorityOBDFreezeFrame
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) HighPriorityEventStrgIndexPtr,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_DATACTL_OBD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

