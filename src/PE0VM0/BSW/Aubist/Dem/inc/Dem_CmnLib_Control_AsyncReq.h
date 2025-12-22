/* Dem_CmnLib_Control_AsyncReq_h(v5-9-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_AsyncReq/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_CONTROL_ASYNCREQ_H
#define DEM_CMNLIB_CONTROL_ASYNCREQ_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "Dem_CmnIf_Control.h"
#include "Dem_CmnLib_Control.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Return value of asynchronous processing function. */
#define DEM_ASYNCRET_UPD_FR                 ((Dem_u08_AsyncExecReturnType)0x01U)
#define DEM_ASYNCRET_NOUPD_FR               ((Dem_u08_AsyncExecReturnType)0x00U)

#define DEM_ASYNCRET_NEED_REGEN_ODR         ((Dem_u08_AsyncExecReturnType)0x02U)
#define DEM_ASYNCRET_NONEED_REGEN_ODR       ((Dem_u08_AsyncExecReturnType)0x00U)

#define DEM_ASYNCRET_EXIT_ASYNC_PROC        ((Dem_u08_AsyncExecReturnType)0x04U)
#define DEM_ASYNCRET_CONTINUE_ASYNC_PROC    ((Dem_u08_AsyncExecReturnType)0x00U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Function type */
/****************************************************************************/
/* Parameters    | Index        :   async request parameter - 1             */
/*               | Status       :   async request parameter - 2             */
/*               | DataBuffPtr  :   async request parameter - 3             */
/* Return Value  | uint8 : This value sets the logical disjunction of each  */
/*               |         of the following values.                         */
/*               |  - 1. FaultRecord update information.                    */
/*               |     DEM_ASYNCRET_UPD_FR   : Updated.                     */
/*               |     DEM_ASYNCRET_NOUPD_FR : Not updated.                 */
/*               |                                                          */
/*               |  - 2. Whether the OrderList should be regenerated after  */
/*               |    this function.                                        */
/*               |     DEM_ASYNCRET_NEED_REGEN_ODR   : Need re-generate.    */
/*               |     DEM_ASYNCRET_NONEED_REGEN_ODR : No need re-generate. */
/*               |                                                          */
/*               |  - 3. Whether to exit or continue asynchronous process-  */
/*               |    ing after this function.                              */
/*               |     DEM_ASYNCRET_EXIT_ASYNC_PROC     : Exit.             */
/*               |     DEM_ASYNCRET_CONTINUE_ASYNC_PROC : Continue.         */
/****************************************************************************/
typedef P2FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE, DemAsyncReqFncPTR )
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC )                Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC )                 Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )    DataBuffPtr
);

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_Control_EventEntry          */
/*----------------------------------*/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEvent
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#if  ( DEM_MONITORDATA_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventWithMonitorData
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */
#if  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventStatusForUserDefinedMemoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_InitializeEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_AgingEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NormalizeEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_ActiveFaultEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);

/*----------------------------------*/
/*  Dem_Control_OpCycle             */
/*----------------------------------*/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_RestartOpCycleFirstProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetCycleQualifiedProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_RestartOpCycleContinueProcess
( void );


/*----------------------------------*/
/*  Dem_Control_PFC                 */
/*----------------------------------*/
#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_PFCRecordUpdateProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_PFC_RECORD_SUPPRESSION_SUPPORT -STD_ON- */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_ClearAllPFCProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_PFC_SUPPORT -STD_ON- */

/*----------------------------------*/
/*  Dem_Control_DTR                 */
/*----------------------------------*/
#if ( DEM_DTR_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetDTRProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_DTR_SUPPORT -STD_ON- */

/*----------------------------------*/
/*  Dem_Control_IUMPR               */
/*----------------------------------*/
#if ( DEM_IUMPR_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRDenCondition
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRDenRelease
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRFaultDetect
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */
#endif /* DEM_IUMPR_SUPPORT -STD_ON- */

/*----------------------------------*/
/*  Dem_Control_Readiness           */
/*----------------------------------*/
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventDisabled
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_PID_READINESS_SUPPORT -STD_ON- */

/*----------------------------------*/
/*  Dem_Control_SpecificEventEntry  */
/*----------------------------------*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetSpecificEventProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_SPECIFIC_EVENT_SUPPORT -STD_ON- */

/*----------------------------------*/
/*  Dem_Control_NotifyEvtAvl        */
/*----------------------------------*/
#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyEventAvailable
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_EVENT_AVAILABILITY_FIM_REPORT -STD_ON- */

#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
/*----------------------------------*/
/*  Dem_Control_OccrDTC             */
/*----------------------------------*/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyDTCStatusChanged
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif  /* ( DEM_TRIGGER_DCM_REPORTS == STD_ON )    */


/*--------------------------------------*/
/*  Dem_Control_EventUdsStatusHistory   */
/*--------------------------------------*/
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_ResetEventUdsStatusHistoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventUdsStatusHistoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/*--------------------------------------*/
/*  Dem_Control_IndPrimary              */
/*--------------------------------------*/
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetMILAtShortMIProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CMNLIB_CONTROL_ASYNCREQ_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

