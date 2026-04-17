/* Dem_AsyncReqTable_c(v5-9-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/AsyncReqTable/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_AsyncReqTableType        , DEM_CONFIG_DATA ) Dem_ExecAsyncReqTable[ DEM_ASYNCREQ_NUM ] =
{
    /*  Function                                                    ExecInitStatus                        OrderListMustFixed                  ChkEventAvailable               ChkDTCSettingStatus           ClrDTCStatus by Primary   ClrDTCStatus by UsrDef       ClrDTCStatus with EventIdx   UpdMonitorStatus              AsyncDataQIndex */
    {   &Dem_Control_SetEvent,                                      DEM_CTL_STS_INIT_PREINIT_COMPLETE,  ( DEM_FNCATTR_ATR_MSTFIX_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_EXE_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_EXE_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_SetEventStatus               */
    {   &Dem_Control_RestartOpCycleFirstProcess,                    DEM_CTL_STS_INIT_PREINIT_COMPLETE,  ( DEM_FNCATTR_ATR_MSTFIX_ORDERLIST  | DEM_FNCATTR_NOT_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_NOT_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_NOT_CLRDTCEVT  | DEM_FNCATTR_NOT_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_RestartOperationCycle        */
    {   &Dem_Control_InitializeEventStatus,                         DEM_CTL_STS_INIT_INITIALIZING,      ( DEM_FNCATTR_ATR_NONEED_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_EXE_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_EXE_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_InitializeEventStatus        */
    {   &Dem_Control_AgingEventStatus,                              DEM_CTL_STS_INIT_INITIALIZING,      ( DEM_FNCATTR_ATR_NONEED_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_EXE_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_EXE_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_AgingEventStatus             */
    {   &Dem_Control_NormalizeEventStatus,                          DEM_CTL_STS_INIT_INITIALIZING,      ( DEM_FNCATTR_ATR_NONEED_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_EXE_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_EXE_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_NormalizeEventStatus         */
    {   &Dem_Control_SetEventStatusForUserDefinedMemoryProcess,     DEM_CTL_STS_INIT_PREINIT_COMPLETE,  ( DEM_FNCATTR_ATR_NONEED_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_NOT_DTCSETTING  | DEM_FNCATTR_NOT_CLRDTC  | DEM_FNCATTR_EXE_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_NOT_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    },  /* Dem_SetEventStatus(UserDefinedMemory) */
    {   &Dem_Control_ActiveFaultEventStatus,                        DEM_CTL_STS_INIT_INITIALIZING,      ( DEM_FNCATTR_ATR_MSTFIX_ORDERLIST  | DEM_FNCATTR_CHK_EVTAVAILABLE  | DEM_FNCATTR_CHK_DTCSETTING  | DEM_FNCATTR_EXE_CLRDTC  | DEM_FNCATTR_NOT_UDMCLRDTC  | DEM_FNCATTR_EXE_CLRDTCEVT  | DEM_FNCATTR_EXE_UPDMONSTS ),  DEM_ASYNCDATAQUETABLEINDEX_INVALID    }   /* Dem_ActiveFaultEventStatus       */
};

CONST( AB_83_ConstV Dem_u08_AsyncReqTableIndexType        , DEM_CONFIG_DATA ) Dem_AsyncReqNum     = DEM_ASYNCREQ_NUM;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#ifndef JGXSTACK
#else /* JGXSTACK */
/****************************************************************************/
/* Function Name | Dem_AsyncReqFnc_ForStack                                 */
/* Description   | DemAsyncReqFnc for measuring stack size.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index :                                             */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] Status :                                            */
/*               |        Monitor test result.                              */
/*               | [in] DataBuffPtr :                                       */
/*               |        The pointer of the data buffer.                   */
/* Return Value  | Dem_u08_AsyncExecReturnType  :                           */
/*               |             FaultRecord update information and           */
/*               |             whether the OrderList should be regenerated  */
/*               |             after this function.                         */
/*               |  DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NEED_REGEN_ODR   :   */
/*               |                      fault record is updated.            */
/*               |                      need re-generate orderlist.         */
/*               |                                                          */
/*               |  DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR :   */
/*               |                      fault record is updated.            */
/*               |                      no need re-generate orderlist.      */
/*               |                                                          */
/*               |  DEM_ASYNCRET_NOUPD_FR   :                               */
/*               |                      fault record is not updated.        */
/*               |                      no need re-generate orderlist.      */
/* Notes         | At the caller, the value of DataBuffPtr is               */
/*               | guaranteed.                                              */
/*               | Caller:Dem_Control_SetEventLoop                          */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_AsyncReqFnc_ForStack
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC )                Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC )                Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )    DataBuffPtr
)
{
    /* Auto variable definition */
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) requestGenOrderListFlg;

    requestGenOrderListFlg = Dem_Control_SetEvent( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_RestartOpCycleFirstProcess( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_InitializeEventStatus( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_AgingEventStatus( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_NormalizeEventStatus( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_SetEventStatusForUserDefinedMemoryProcess( Index, Status, DataBuffPtr );
    requestGenOrderListFlg = Dem_Control_ActiveFaultEventStatus( Index, Status, DataBuffPtr );

    return requestGenOrderListFlg;
}
#endif /* JGXSTACK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
