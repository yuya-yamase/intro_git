/* Dem_Control_AsyncReq_c(v5-7-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_AsyncReq/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"

#include "Dem_Control_cmn_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Control_SetEventLoop
( void );

static FUNC( void, DEM_CODE ) Dem_Control_GenerateOrderList
( void );

static FUNC( void, DEM_CODE ) Dem_Control_JudgeAndGenerateOrderList
(
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) RequestGenOrderListFlg,
    VAR( boolean, AUTOMATIC ) OrderListMustFixedFlg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GenOrderListPendingFlgPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GeneratedOrderListFlgPtr
);

static FUNC( void, DEM_CODE ) Dem_Control_LastJudgeAndGenerateOrderList
(
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) RequestGenOrderListFlg,
    VAR( boolean, AUTOMATIC ) GenOrderListPendingFlg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GeneratedOrderListFlgPtr
);

static FUNC( void, DEM_CODE ) Dem_Control_SetSettingEventMode
(
    VAR( boolean, AUTOMATIC ) SettingEvent
);

static FUNC( void, DEM_CODE ) Dem_Control_ClearSettingEventMode
(
    VAR( boolean, AUTOMATIC ) SettingEvent,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) opcycleUpdateState
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( boolean, DEM_VAR_NO_INIT )  Dem_CtlExecAsyncProcessFlag;    /*  execute async request process.  TRUE: execute now. FALSE:not execute async process. */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Control_InitAsyncReqLoop                             */
/* Description   | Initializes asyncronus request loop.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitAsyncReq
( void )
{
    Dem_CtlExecAsyncProcessFlag   = (boolean)FALSE;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckExecAsyncProcess                        */
/* Description   | execute async process or not.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   Async processing now.                   */
/*               |        FALSE :   Async process is not execute now.       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_CheckExecAsyncProcess   /* MISRA DEVIATION */
( void )
{
    return Dem_CtlExecAsyncProcessFlag;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetEventProcess                              */
/* Description   | Processes set event.                                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Dem_MainFunction                                         */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_SetEventProcess
( void )
{
    VAR( boolean, AUTOMATIC ) enableSetEventLoopFlag = (boolean)FALSE;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) opcycleUpdateState;

    SchM_Enter_Dem_CheckClearDTCStatus();

    /* Check during clear processing */
    execClearDTC = Dem_Control_CheckExecClearDTCProcess();
    if( execClearDTC == (boolean)FALSE )
    {
        /* When not in clear processing */
        /* Set loop execution flag of event registration ON */
        enableSetEventLoopFlag = (boolean)TRUE;

        /*  start of async process.     */
        Dem_CtlExecAsyncProcessFlag =   (boolean)TRUE;

    }
    else
    {
        /* No process */
    }

    SchM_Exit_Dem_CheckClearDTCStatus();

    /* Check during clear processing2 */
    if( enableSetEventLoopFlag == (boolean)TRUE )
    {
        /* Loop processing execution of event registration */
        Dem_Control_SetEventLoop();

        /*  check update operationcycle status.(because only update operation cycle job is execute continuous over next cycle.) */
        opcycleUpdateState = Dem_Control_GetOpCycleUpdateState();
        if( opcycleUpdateState != DEM_IRT_PENDING )
        {
            /*  end of async process.       */
            Dem_CtlExecAsyncProcessFlag =   (boolean)FALSE;
        }
        else
        {
            /* When in operation cycle state setting processing, as state has been updated, do nothing */
            /* No process */
        }
    }
    else
    {
        /* No process*/
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetEventLoop                                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetEventLoop
( void )
{
    VAR( uint8, AUTOMATIC ) dataBuffer[DEM_ASYNCDATAQUE_ITEMSIZE_MAX];
    VAR( boolean, AUTOMATIC ) settingEvent;
    VAR( boolean, AUTOMATIC ) genOrderListPendingFlg;
    VAR( boolean, AUTOMATIC ) generatedOrderListFlg;
    VAR( boolean, AUTOMATIC ) orderListMustFixedFlg;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) setEventStatus;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) setNewEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retDequeue;
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) asyncFuncRetVal;
    VAR( Dem_u08_AsyncReqFuncAttrType, AUTOMATIC ) funcAttribute;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) setEventIndex;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) setEventNum;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) opcycleUpdateState;

    /* Initialize return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    asyncFuncRetVal         = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    genOrderListPendingFlg  = (boolean)FALSE;   /* Initial value : no pending generate orderlist request.   */
    generatedOrderListFlg   = (boolean)FALSE;   /* Initial value : no complete generate orderlist.          */
    loopEnd                 = (boolean)FALSE;

    setEventIndex           = DEM_ASYNCREQ_PARAM_INDEX_INVALID;
    setEventStatus          = DEM_ASYNCREQ_PARAM_STATUS_INVALID;
    settingEvent            = (boolean)FALSE;
    setEventNum             = Dem_CtlSetEventNum;
    setNewEventKind         = Dem_AsyncReqNum;
    asyncReqNum             = Dem_AsyncReqNum;

    /* Judge whether to dequeue */
    opcycleUpdateState = Dem_Control_GetOpCycleUpdateState();
    if( opcycleUpdateState != DEM_IRT_PENDING )
    {
        for( loopCount = (Dem_u16_EventQueueIndexType)0U; loopCount < setEventNum; loopCount++ )
        {
            /* Because it is not in operation cycle state setting, dequeue */
            retDequeue = Dem_AsyncReq_Dequeue( &setNewEventKind, &setEventIndex, &setEventStatus, &dataBuffer[0] );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / 0 */
            if( retDequeue == DEM_IRT_OK )
            {
                Dem_Control_SetSettingEventMode( settingEvent );
                settingEvent = (boolean)TRUE;

                asyncReqIndex = setNewEventKind;
                if( asyncReqIndex < asyncReqNum )                                                                           /* [GUD:if]asyncReqIndex */
                {
                    funcAttribute = Dem_ExecAsyncReqTable[ asyncReqIndex ].FuncAttribute;                                   /* [GUD]asyncReqIndex */
                    if( ( funcAttribute & DEM_FNCATTR_ATR_MSTFIX_ORDERLIST ) == DEM_FNCATTR_ATR_MSTFIX_ORDERLIST )
                    {
                        /*  When the orderlist must fixed before execute asyncronus jobs.       */
                        orderListMustFixedFlg = (boolean)TRUE;
                    }
                    else
                    {
                        /*  When no need to fixed the orderlist before execute asyncronus jobs. */
                        orderListMustFixedFlg = (boolean)FALSE;
                    }

                    /*  Judge generate orderlist.           */
                    Dem_Control_JudgeAndGenerateOrderList( asyncFuncRetVal, orderListMustFixedFlg, &genOrderListPendingFlg, &generatedOrderListFlg );
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
                    if( generatedOrderListFlg == ( boolean )TRUE )
                    {
                        /* Update OccrDTCRecord */
                        Dem_OccrDTC_UpdateOccrDTCRecord();
                    }

                    Dem_OccrDTC_LatchOccrDTCRecord();
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )          */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
                    if( ( funcAttribute & DEM_FNCATTR_EXE_UPDMONSTS ) == DEM_FNCATTR_EXE_UPDMONSTS )
                    {
                        /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
                        Dem_MonSts_SetAsyncUpdateMode( DEM_MONSTS_ASYNCUPD_NORMAL );
                    }
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

#ifndef JGXSTACK
                    /*  Execute asyncronus jobs.            */
                    asyncFuncRetVal = Dem_ExecAsyncReqTable[ asyncReqIndex ].Func( setEventIndex, setEventStatus, &dataBuffer[0] );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / 0 */
#else /* JGXSTACK */
                    asyncFuncRetVal = Dem_AsyncReqFnc_ForStack( setEventIndex, setEventStatus, &dataBuffer[0] );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / 0 */
#endif /* JGXSTACK */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
                    if( ( funcAttribute & DEM_FNCATTR_EXE_UPDMONSTS ) == DEM_FNCATTR_EXE_UPDMONSTS )
                    {
                        /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
                        Dem_MonSts_SetAsyncMonitorStatus( setEventIndex );
                    }
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

                    if( ( asyncFuncRetVal & DEM_ASYNCRET_EXIT_ASYNC_PROC ) == DEM_ASYNCRET_EXIT_ASYNC_PROC )
                    {
                        /* When the executed asynchronous processing function sets exit of the asynchronous processing loop as the return value. */
                        loopEnd = (boolean)TRUE;
                    }
                }
            }
            else
            {
                /* Event queue became empty or an error occurs in dequeue processing. */
                loopEnd = (boolean)TRUE;
            }

            if( loopEnd == (boolean)TRUE )
            {
                /* Exit the asynchronous event processing loop. */
                break;
            }
        }
    }
    else
    {
        /* As in operation cycle state setting, continue processing of the previous cycle. */
        settingEvent = (boolean)TRUE;
        asyncFuncRetVal = Dem_Control_RestartOpCycleContinueProcess();
    }

    /*  generate order list. -last-          */
    Dem_Control_LastJudgeAndGenerateOrderList( asyncFuncRetVal, genOrderListPendingFlg, &generatedOrderListFlg );

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if( generatedOrderListFlg == ( boolean )TRUE )
    {
        /* Update OccrDTCRecord */
        Dem_OccrDTC_UpdateOccrDTCRecord();
    }
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )          */

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if( generatedOrderListFlg == (boolean)TRUE )
    {
        /*  OrderList is re-generated.      */
        Dem_PID_ConfirmedDTCClear();
    }
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )             */

    opcycleUpdateState = Dem_Control_GetOpCycleUpdateState();
    Dem_Control_ClearSettingEventMode( settingEvent, opcycleUpdateState );

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_GenerateOrderList                            */
/* Description   | Failure occurrence order list generation                 */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_GenerateOrderList
( void )
{
    /* Re-build generation sequence table from the current records */
    Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
    Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_Data_GenerateMILFaultOrderList();
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )          */

    Dem_Data_ClearSearchFFDIndex();

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    /*  update PFC record. */
    Dem_DTC_UpdatePFCRecord();

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_IndMI_UpdateB1Record();

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_JudgeAndGenerateOrderList                    */
/* Description   | Judge and Generate OrderList                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] RequestGenOrderListFlg                              */
/*               |          :  FaultRecord update information and           */
/*               |             whether the OrderList should be regenerated. */
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
/*               |                                                          */
/*               | [in] OrderListMustFixedFlg                               */
/*               |      :   OrderList will be Must Fixed.                   */
/*               |              FALSE   :    no need fixed.                 */
/*               |              TRUE    :    must be fixed.                 */
/*               | [in/out] GenOrderListPendingFlgPtr                       */
/*               |      :   Re-Generate is pending or not.                  */
/*               |              FALSE   :    no pending. -OrderList fixed-  */
/*               |              TRUE    :    pending re-generate.           */
/*               | [in/out] GeneratedOrderListFlgPtr                        */
/*               |      :   Generated OrderList or not. -accumerate-        */
/*               |              FALSE   :    no generate.                   */
/*               |              TRUE    :    re-generated.                  */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_JudgeAndGenerateOrderList
(
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) RequestGenOrderListFlg,
    VAR( boolean, AUTOMATIC ) OrderListMustFixedFlg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GenOrderListPendingFlgPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GeneratedOrderListFlgPtr
)
{
    VAR( boolean, AUTOMATIC ) genOrderListPendingFlg;

    genOrderListPendingFlg     =   *GenOrderListPendingFlgPtr;

    if ( ( RequestGenOrderListFlg & DEM_ASYNCRET_UPD_FR ) == DEM_ASYNCRET_UPD_FR )
    {
        if ( ( RequestGenOrderListFlg & DEM_ASYNCRET_NEED_REGEN_ODR ) == DEM_ASYNCRET_NEED_REGEN_ODR )
        {
            /*  pending re-generate OrderList.      */
            genOrderListPendingFlg      =   ( boolean )TRUE;
        }
        else
        {
            /*  OrderList re-generated already.     */
            *GeneratedOrderListFlgPtr   =   ( boolean )TRUE;
        }
    }

    if ( OrderListMustFixedFlg == ( boolean )TRUE )
    {
        if ( genOrderListPendingFlg == ( boolean )TRUE )
        {
            /*  generate order list.            */
            Dem_Control_GenerateOrderList();

            /*  set generate information.       */
            genOrderListPendingFlg      =   ( boolean )FALSE;
            *GeneratedOrderListFlgPtr   =   ( boolean )TRUE;
        }
    }

    /*  set orderlist generate flag.    */
    *GenOrderListPendingFlgPtr =   genOrderListPendingFlg;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_LastJudgeAndGenerateOrderList                */
/* Description   | Judge & Generate OrderList                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RequestGenOrderListFlg                              */
/*               |          :  FaultRecord update information and           */
/*               |             whether the OrderList should be regenerated. */
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
/*               |                                                          */
/*               | [in/out] GenOrderListPendingFlgPtr                       */
/*               |      :   Re-Generate is pending or not.                  */
/*               |              FALSE   :    no pending. -OrderList fixed-  */
/*               |              TRUE    :    pending re-generate.           */
/*               | [in/out] GeneratedOrderListFlgPtr                        */
/*               |      :   Generated OrderList or not. -accumerate-        */
/*               |              FALSE   :    no generate.                   */
/*               |              TRUE    :    re-generated.                  */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_LastJudgeAndGenerateOrderList
(
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) RequestGenOrderListFlg,
    VAR( boolean, AUTOMATIC ) GenOrderListPendingFlg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) GeneratedOrderListFlgPtr
)
{
    VAR( boolean, AUTOMATIC ) genOrderListPendingFlg;

    genOrderListPendingFlg     =   GenOrderListPendingFlg;

    if ( ( RequestGenOrderListFlg & DEM_ASYNCRET_UPD_FR ) == DEM_ASYNCRET_UPD_FR )
    {
        if ( ( RequestGenOrderListFlg & DEM_ASYNCRET_NEED_REGEN_ODR ) == DEM_ASYNCRET_NEED_REGEN_ODR )
        {
            /*  pending re-generate OrderList.      */
            genOrderListPendingFlg      =   ( boolean )TRUE;
        }
        else
        {
            /*  OrderList re-generated already.     */
            *GeneratedOrderListFlgPtr   =   ( boolean )TRUE;
        }
    }

    if ( genOrderListPendingFlg == ( boolean )TRUE )
    {
        /*  generate order list.            */
        Dem_Control_GenerateOrderList();
        *GeneratedOrderListFlgPtr   =   ( boolean )TRUE;
    }

    return ;
}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions -mode-                                           */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_SetSettingEventMode                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SettingEvent :                                      */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetSettingEventMode
(
    VAR( boolean, AUTOMATIC ) SettingEvent
)
{
    /* This function is executed at the time when dequeue                    */
    /* processing of Dem_Control_SetEventLoop is successful.                 */
    /* Argument SettingEvent is assigned by a local variable that shows      */
    /* whether to execute an event processing in Dem_Control_SetEventLoop.   */
    /* It is set to TRUE after this function is called.                      */
    /* For Mode notification is notified only for the first event processing */
    /* it is executed when SettingEvent is FALSE                             */
    if( SettingEvent == (boolean)FALSE )
    {
        Dem_ModeMng_SetMode( DEM_MODE_SETTING_EVENT );
    }
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearSettingEventMode                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SettingEvent :                                      */
/*               |                                                          */
/*               | [in] opcycleUpdateState :                                */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearSettingEventMode
(
    VAR( boolean, AUTOMATIC ) SettingEvent,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) opcycleUpdateState
)
{
    if( SettingEvent == (boolean)TRUE )
    {
        if( opcycleUpdateState != DEM_IRT_PENDING )
        {
            /* When it is not in operation cycle setting, clear mode */
            Dem_ModeMng_ClearMode( DEM_MODE_SETTING_EVENT );
        }
        else
        {
            /* When operation cycle setting extends into the next cycle, not clear mode */
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

