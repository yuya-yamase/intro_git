/* Dem_AsyncReq_local_h(v5-0-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AsyncReq_local/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_ASYNCREQ_LOCAL_H
#define DEM_ASYNCREQ_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_EVENT_QUEUE_MIN_INDEX             ((Dem_u16_EventQueueIndexType)0U)
#define DEM_EVENT_QUEUE_MAX_INDEX             (Dem_EventQueueSize - (Dem_u16_EventQueueIndexType)1U)
#define DEM_EVENT_QUEUE_NUMBER_EMPTY          ((Dem_u16_EventQueueIndexType)0U)
#define DEM_EVENT_QUEUE_CLEAR_NUMBER_NONE     ((Dem_u16_EventQueueIndexType)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/*----------------------------------*/
/*  Dem_AsyncReqData                */
/*----------------------------------*/
FUNC( void, DEM_CODE_TRUST ) Dem_AsyncReqData_ClearQueData       /*  PreInit section     */
( void );
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

/*----------------------------------*/
/*  Dem_EventQueue                  */
/*----------------------------------*/
FUNC( void, DEM_CODE_TRUST ) Dem_EventQueue_PreInit       /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_AsyncReqData                */
/*----------------------------------*/
#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
FUNC( void, DEM_CODE ) Dem_AsyncReqData_RefreshRAM
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReqData_RegistQue
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    P2VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC, AUTOMATIC ) QueIndexPtr
);
FUNC( void, DEM_CODE ) Dem_AsyncReqData_SetQueData
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBufferPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReqData_ReleaseQue
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBufferPtr
);
FUNC( void, DEM_CODE ) Dem_AsyncReqData_ReleaseQueWithoutData
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex
);
FUNC( void, DEM_CODE ) Dem_AsyncReqData_ReleaseQueIndex
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex
);
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( void, DEM_CODE ) Dem_AsyncReqData_GetEventStatus
(
    VAR( Dem_u08_AsyncDataQueTableIndexType, AUTOMATIC ) AsyncDataQueIndex,
    VAR( Dem_u08_AsyncDataQueIndexType, AUTOMATIC ) QueIndex,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) EventStatusPtr
);
#endif /* DEM_TRIGGER_FIM_REPORTS -STD_ON- */
#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */

/*----------------------------------*/
/*  Dem_EventQueue                  */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_EventQueue_Shutdown
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_Enqueue
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_Dequeue
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
);
FUNC( boolean, DEM_CODE ) Dem_EventQueue_IsQueueEmpty
( void );
FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearStatus
( void );
FUNC( void, DEM_CODE ) Dem_EventQueue_SetClearEvent
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( Dem_u16_EventQueueIndexType, DEM_CODE ) Dem_EventQueue_GetReadIndex
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventQueue_CheckQueueNext
(
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadIndexPtr,
    P2VAR( Dem_u16_EventQueueIndexType, AUTOMATIC, AUTOMATIC ) ReadCountPtr,
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC ) KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC ) IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr
);
#endif /* DEM_TRIGGER_FIM_REPORTS -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_ASYNCREQ_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
