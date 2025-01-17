/* Dem_CmnLib_AsyncReq_h(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_AsyncReq/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_ASYNCREQ_H
#define DEM_CMNLIB_ASYNCREQ_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "Dem_CmnLib_Control_AsyncReq.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_ASYNCREQ_PARAM_INDEX_INVALID        ((Dem_u16_AsyncReqItemAType)0xFFFFU)
#define DEM_ASYNCREQ_PARAM_STATUS_INVALID       ((Dem_u08_AsyncReqItemBType)0xFFU)

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
/* Event status stored position in the data queue. */
#define DEM_ASYNCDATAQUE_EVENTSTATUS_POS        ((Dem_u08_AsyncDataQueItemSizeType)0U)

#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

/* OrderListMustFixed */
#define DEM_FNCATTR_ATR_MSTFIX_ORDERLIST        ((Dem_u08_AsyncReqFuncAttrType)0x01U)
#define DEM_FNCATTR_ATR_NONEED_ORDERLIST        ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* ChkEventAvailable */
#define DEM_FNCATTR_CHK_EVTAVAILABLE            ((Dem_u08_AsyncReqFuncAttrType)0x02U)
#define DEM_FNCATTR_NOT_EVTAVAILABLE            ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* ChkDTCSettingStatus */
#define DEM_FNCATTR_CHK_DTCSETTING              ((Dem_u08_AsyncReqFuncAttrType)0x04U)
#define DEM_FNCATTR_NOT_DTCSETTING              ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* UpdMonitorStatus */
#define DEM_FNCATTR_EXE_UPDMONSTS               ((Dem_u08_AsyncReqFuncAttrType)0x08U)
#define DEM_FNCATTR_NOT_UPDMONSTS               ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* ClrDTCStatus by PrimaryMemory */
#define DEM_FNCATTR_EXE_CLRDTC                  ((Dem_u08_AsyncReqFuncAttrType)0x10U)
#define DEM_FNCATTR_NOT_CLRDTC                  ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* ClrDTCStatus by UserDefinedMemory */
#define DEM_FNCATTR_EXE_UDMCLRDTC               ((Dem_u08_AsyncReqFuncAttrType)0x20U)
#define DEM_FNCATTR_NOT_UDMCLRDTC               ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/* ClrDTCStatus with EventCtrlIndex  */
#define DEM_FNCATTR_EXE_CLRDTCEVT               ((Dem_u08_AsyncReqFuncAttrType)0x40U)
#define DEM_FNCATTR_NOT_CLRDTCEVT               ((Dem_u08_AsyncReqFuncAttrType)0x00U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    DemAsyncReqFncPTR                       Func;
    Dem_u08_InitStatusType                  ExecInitStatus;
    Dem_u08_AsyncReqFuncAttrType            FuncAttribute;
    Dem_u08_AsyncDataQueTableIndexType      AsyncDataQueIndex;
} Dem_AsyncReqTableType;

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
typedef struct
{
    uint8*      BuffPtr;
    volatile Dem_u08_AsyncDataQueIndexType*      EmptyPosVPtr;
    volatile Dem_u08_AsyncDataQueIndexType*      StoredItemNumVPtr;
    Dem_u08_AsyncDataQueIndexType                ItemNum;
    Dem_u08_AsyncDataQueItemSizeType             ItemSize;
} Dem_AsyncDataQueTableType;
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_TRUST ) Dem_AsyncReq_PreInit       /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_AsyncReq                    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_AsyncReq_Shutdown
( void );
#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
FUNC( void, DEM_CODE ) Dem_AsyncReq_RefreshRAM
( void );
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_Enqueue
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
);
#if ( DEM_ASYNCDATAQUE_USE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_EnqueueWithData
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
#endif /* DEM_ASYNCDATAQUE_USE -STD_ON- */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_Dequeue
(
    P2VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC, AUTOMATIC )  KindPtr,
    P2VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC, AUTOMATIC )  IndexPtr,
    P2VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC, AUTOMATIC ) StatusPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
FUNC( void, DEM_CODE ) Dem_AsyncReq_SetClearStatus
( void );
FUNC( void, DEM_CODE ) Dem_AsyncReq_SetClearEvent
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_JudgeReqCondition
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status
);
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( Dem_u16_EventQueueIndexType, DEM_CODE ) Dem_AsyncReq_GetReadIndex
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AsyncReq_CheckQueueNext
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

#endif /* DEM_CMNLIB_ASYNCREQ_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
