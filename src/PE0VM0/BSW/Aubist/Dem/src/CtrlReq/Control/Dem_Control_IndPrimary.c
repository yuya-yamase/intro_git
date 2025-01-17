/* Dem_Control_IndPrimary_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_IndPrimary/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_WWHObd_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_WWHOBD.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_INDMI_CYC_COUNTER_INITIAL              ((Dem_u32_B1CounterCalcCycleCounterType)0x0000U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u32_B1CounterCalcCycleCounterType, DEM_VAR_NO_INIT )    Dem_CalcB1CounterCycleCounter;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_InitIndMI                                    */
/* Description   | Initialization of calculation cycle counter.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitIndMI
( void )
{
    Dem_CalcB1CounterCycleCounter = DEM_INDMI_CYC_COUNTER_INITIAL;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetB1Counter                                 */
/* Description   | Get B1 Counter                                           */
/* Preconditions | none                                                     */
/* Parameters    | [out] B1Counter      : B1Counter.                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : successful.                          */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetB1Counter
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal      =   DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /*--------------------------------------------------------------------------*/
        /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
        /* These are the reasons why this function needs to get exclusive.          */
        /*  - This function call [DataMng] function directory.                      */
        /*  - This function called from SW-C/Dcm context.                           */
        /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
        SchM_Enter_Dem_IndMI();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_IndMI();
        /*--------------------------------------------------------------------------*/

        Dem_IndMI_GetB1Counter( B1CounterPtr );
        retVal      =   DEM_IRT_OK;

    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetB1CounterByEventId                        */
/* Description   | Get B1 Counter by EventId.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventId        : EventId.                          */
/*               | [out] B1Counter      : B1Counter.                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : successful.                          */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_Control_GetActiveFault.         */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetB1CounterByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_B1CounterOutputType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) chkClass;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal      =   DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );    /* [GUD:RET:DEM_IRT_OK]eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );    /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED:eventCtrlIndex ] eventStrgIndex */

            /*  check OBD event or not.         */
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( eventStrgIndex );   /* [GUD]eventStrgIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                chkClass        =   Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( eventStrgIndex );         /* [GUD]eventStrgIndex */
                if ( chkClass == (boolean)TRUE )
                {
                    /*--------------------------------------------------------------------------*/
                    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                    /* These are the reasons why this function needs to get exclusive.          */
                    /*  - This function call [DataMng] function directory.                      */
                    /*  - This function called from SW-C/Dcm context.                           */
                    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                    SchM_Enter_Dem_IndMI();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                    SchM_Exit_Dem_IndMI();
                    /*--------------------------------------------------------------------------*/

                    Dem_IndMI_GetB1CounterByEventStrgIndex_By6Minutes( eventStrgIndex, B1CounterPtr );  /* [GUD]eventStrgIndex */
                    retVal  =   DEM_IRT_OK;
                }
                else
                {
                    retVal  =   DEM_IRT_WRONG_DTC;
                }
            }
            else
            {
                retVal  =   DEM_IRT_WRONG_DTC;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetMILAtShortMI                              */
/* Description   | set MIL at short MI.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] MILStatus : MIL status.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK.                                       */
/*               |        DEM_IRT_NG.                                       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetMILAtShortMI
(
    VAR( boolean, AUTOMATIC ) MILStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_DemBooleanType, AUTOMATIC ) setMILStatus;

    retVal = DEM_IRT_NG;

    /*  parameter check.        */
    setMILStatus    =   DEM_BOOLEAN_FALSE;
    if ( MILStatus == (boolean)TRUE )
    {
        setMILStatus    =   DEM_BOOLEAN_TRUE;
    }

    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SETMILATSHORTMI, DEM_ASYNCREQ_PARAM_INDEX_INVALID, (Dem_u08_AsyncReqItemBType)setMILStatus );
    if( retTempVal == DEM_IRT_OK )
    {
        retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_SETMILATSHORTMI, DEM_ASYNCREQ_PARAM_INDEX_INVALID, (Dem_u08_AsyncReqItemBType)setMILStatus );
        if( retTempVal == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetMILAtShortMIProcess                       */
/* Description   | set MIL at short MI.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] Index       :                                       */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetMILAtShortMIProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,  /* MISRA DEVIATION */
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;

    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_IndMI_SetMILAtShortMI( (Dem_u08_DemBooleanType)Status );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_UpdateB1CounterProcess                       */
/* Description   | update B1 Counter process.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateB1CounterProcess
( void )
{
    VAR( Dem_u32_B1CounterCalcCycleCounterType, AUTOMATIC )    wwhOBDTimeSinceEngineStartDivideCycleCount;

    wwhOBDTimeSinceEngineStartDivideCycleCount   =   Dem_WWHOBDTimeSinceEngineStartDivideCycleCount;

    Dem_CalcB1CounterCycleCounter = Dem_CalcB1CounterCycleCounter + (Dem_u32_B1CounterCalcCycleCounterType)1U;  /*  no wrap around  */
    if( Dem_CalcB1CounterCycleCounter >= wwhOBDTimeSinceEngineStartDivideCycleCount )
    {
        Dem_CalcB1CounterCycleCounter = DEM_INDMI_CYC_COUNTER_INITIAL;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_IndMI_UpdateB1Counter();

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }
    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
