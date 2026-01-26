/* Dem_Rc_OdrLst_h(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_OdrLst/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_RC_ODRLST_H
#define DEM_RC_ODRLST_H

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
typedef struct
{
    Dem_u08_FaultIndexType  FaultIndex;
    Dem_u16_OccrOrderType  OccurrenceOrder;
} Dem_FaultRegistType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Fault OrderList                 */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_ExecSort
( void );

FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_ApplySortedList
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Fault_GetOccrOrderValue
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_RegistComplete
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) OccurrenceOrder
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Fault_GetFaultIndexByOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);
FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_GetOrderByFaultIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
);
#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_ClearList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Fault_GetNextOccurrenceOrder
(
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_Fault_UpdateNextOccurrenceOrder
(
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) NextOccurrenceOrder
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  Confirmed OrderList             */
/*----------------------------------*/

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ExecSort
( void );

FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ApplySortedList
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetOccrOrderValue
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_RegistComplete
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) OccurrenceOrder
);

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )
FUNC( Dem_u08_OrderIndexType, DEM_CODE ) Dem_OdrLst_Confirmed_GetLastOccurrenceOrder
( void );
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )  */
#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

#if ( DEM_ORDERTYPE_CONFIRMED_ORDERLIST_USE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetFaultIndexByOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_ORDERLIST_USE == STD_ON )  */

FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_GetOrderByFaultIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
);

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_ClearList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_Confirmed_GetNextOccurrenceOrder
(
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_Confirmed_UpdateNextOccurrenceOrder
(
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) NextOccurrenceOrder
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

/*----------------------------------*/
/*  MIL OrderList                   */
/*----------------------------------*/
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OdrLst_MIL_ExecSort
( void );

FUNC( void, DEM_CODE ) Dem_OdrLst_MIL_ApplySortedList
( void );

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_OdrLst_MIL_ClearList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_MIL_GetFaultIndexByOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_MIL_GetOccrOrderValue
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_MIL_RegistComplete
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) OccurrenceOrder
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_MIL_GetNextOccurrenceOrder
(
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )    */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OdrLst_MIL_GetNextOccurrenceOrder
(
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OccurrenceOrderPtr
);

FUNC( void, DEM_CODE ) Dem_OdrLst_MIL_UpdateNextOccurrenceOrder
(
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) NextOccurrenceOrder
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )      */



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_RC_ODRLST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

