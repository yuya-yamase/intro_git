/* Dem_Control_EventEntryCmn_c(v5-9-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventEntryCmn/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_Udm_Control.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if  ( DEM_MONITORDATA_SUPPORT == STD_ON )

#define DEM_DATABUF_EVENTSTATUS        ( DEM_ASYNCDATAQUE_EVENTSTATUS_POS )
#define DEM_DATABUF_MONITORDATA_0      ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)1U))
#define DEM_DATABUF_MONITORDATA_1      ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)2U))
#define DEM_DATABUF_MONITORDATA_2      ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)3U))
#define DEM_DATABUF_MONITORDATA_3      ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)4U))
#define DEM_MONTORDATA_BITSHIFT_8      ((uint8)8U)
#define DEM_MONTORDATA_BITSHIFT_16     ((uint8)16U)
#define DEM_MONTORDATA_BITSHIFT_24     ((uint8)24U)

#endif  /*  ( DEM_MONITORDATA_SUPPORT == STD_ON )   */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetEvent_PrimaryMemory
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventStatusForUserDefinedMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetEvent_UserDefMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetFailedWithSyncFFD_UserDefMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_SetEventStatus                               */
/* Description   | Sets event.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        event ID                                          */
/*               | [in] EventStatus :                                       */
/*               |        event status                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )               */
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
        memKind  = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
        if( memKind != DEM_MEMKIND_PRIMARY )
        {
            /*  userDefinedMemory       */
            retVal  =   Dem_Control_SetEventStatusForUserDefinedMemory( eventCtrlIndex, EventStatus );
        }
        else
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )               */
        {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
            isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

            if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
            {
                retTempVal = Dem_Control_CheckStatusForSetEvent_PrimaryMemory( EventStatus );
                if( retTempVal == DEM_IRT_OK )
                {
                    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_EVENT, eventCtrlIndex, EventStatus );
                    if( retTempVal == DEM_IRT_OK )
                    {
                        retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_EVENT, eventCtrlIndex, EventStatus );
                        if( retTempVal == DEM_IRT_OK )
                        {
                            retVal = DEM_IRT_OK;
                        }
                    }
                }
            }
        }
    }

    return retVal;
}


#if ( DEM_MONITORDATA_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetEventStatusWithMonitorData                */
/* Description   | Set event status with monitorData0.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |            event ID                                      */
/*               | [in] EventStatus :                                       */
/*               |            event status                                  */
/*               | [in] monitorData0:                                       */
/*               |            Monitor test result                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_SetEventStatusWithMonitorData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )               */
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
    VAR( uint8, AUTOMATIC) data[DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE];

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );

    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )     /*  [FuncSw]    */
        memKind  = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
        if( memKind == DEM_MEMKIND_PRIMARY )
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )               */
        {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
            isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

            /*  OK : primary normal events and user defined memory events   */
            /*  NG : primary specific events                                */
            if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
            {
                retTempVal = Dem_Control_CheckStatusForSetEvent_PrimaryMemory( EventStatus );
                if( retTempVal == DEM_IRT_OK )
                {
                    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_EVENT_WITH_MONITORDATA, eventCtrlIndex, EventStatus );
                    if( retTempVal == DEM_IRT_OK )
                    {
                        data[DEM_DATABUF_EVENTSTATUS]   = (uint8)EventStatus;/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_EVENTSTATUS */
                        data[DEM_DATABUF_MONITORDATA_0] = (uint8)monitorData0;/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_0 */
                        data[DEM_DATABUF_MONITORDATA_1] = (uint8)( monitorData0 >> DEM_MONTORDATA_BITSHIFT_8 );/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_1 */
                        data[DEM_DATABUF_MONITORDATA_2] = (uint8)( monitorData0 >> DEM_MONTORDATA_BITSHIFT_16 );/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_2 */
                        data[DEM_DATABUF_MONITORDATA_3] = (uint8)( monitorData0 >> DEM_MONTORDATA_BITSHIFT_24 );/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_3 */

                        retTempVal = Dem_AsyncReq_EnqueueWithData( DEM_ASYNCREQ_EVENT_WITH_MONITORDATA, eventCtrlIndex, &data[0]);  /* [GUD:FixVal]DEM_ASYNCREQ_EVENT_WITH_MONITORDATA *//* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / 0 */
                        if( retTempVal == DEM_IRT_OK )
                        {
                            retVal = DEM_IRT_OK;
                        }
                    }
                }
            }
        }
    }
    return retVal;
}
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetEventStatusForUserDefinedMemory           */
/* Description   | Sets event.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        event ID                                          */
/*               | [in] EventStatus :                                       */
/*               |        event status                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventStatusForUserDefinedMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    retVal = DEM_IRT_NG;

    /*  check event status and memory kind.         */
    retTempVal = Dem_Control_CheckStatusForSetEvent_UserDefMemory( EventCtrlIndex, EventStatus );

    if( retTempVal == DEM_IRT_OK )
    {
        /*  set event status( for userDefinedMemory)       */
        retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_EVENT_FOR_USERDEFINEDMEMORY, EventCtrlIndex, EventStatus );
        if( retTempVal == DEM_IRT_OK )
        {
            retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_EVENT_FOR_USERDEFINEDMEMORY, EventCtrlIndex, EventStatus );
            if( retTempVal == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetEventFailedWithSyncFreezeFrame            */
/* Description   | Sets event.                                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        event ID                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_BUSY : failed(retry possible)             */
/*               |        DEM_IRT_MEMORY_OVERFLOW : failed(memory full)     */
/*               |        DEM_IRT_NG : failed(retry not possible)           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventFailedWithSyncFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) availableStatus;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
        memKind  =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
        if( memKind != DEM_MEMKIND_PRIMARY )
        {
            /*  userdefinedmemory.                                          */
            retTempVal = Dem_Control_CheckStatusForSetFailedWithSyncFFD_UserDefMemory( eventCtrlIndex );

            if( retTempVal == DEM_IRT_OK )
            {
                /*  check condition :   InitStatus      - after Complete Init   */
                /*                      EventAvailable  - available             */
                /*                      DTCSetting      - N/A                   */
                checkStatus = Dem_Control_ChkAfterCompleteInit();
                if( checkStatus == DEM_IRT_OK )
                {
                    (void)Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );        /* [GUD:RET:DEM_IRT_OK] udmEventIndex *//* no return check required */
                    availableStatus = Dem_UdmDataAvl_GetEvtAvl( udmEventIndex );
                    if( availableStatus == (boolean)TRUE )
                    {
                        monitorData0 = ( (Dem_MonitorDataType)EventId ) | DEM_MONITORDATA_SETEVENTFAILED_WITHSYNCFFD;
                        retVal = Dem_UdmControl_SyncEventEntry( udmEventIndex, monitorData0 );
                    }
                }
                else
                {
                    retVal = DEM_IRT_BUSY;
                }
            }
        }
    }

    return retVal;
}
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */


/*--------------------------------------------------------------------------*/
/* Unit Internal functions -process-                                        */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_SetEvent                                     */
/* Description   | Asynchronous processing function of SetEventStatus.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      : Status of the event.                  */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEvent
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    eventId =   Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( (Dem_u16_EventCtrlIndexType)Index );
    monitorData0 = ( (Dem_MonitorDataType)eventId ) | DEM_MONITORDATA_SETEVENTSTATUS;

    retVal  =   Dem_Control_SetEventCommon( (Dem_u16_EventCtrlIndexType)Index, ( Dem_EventStatusType )Status, monitorData0, (boolean)FALSE );

    return retVal;
}


#if  ( DEM_MONITORDATA_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetEventWithMonitorData                      */
/* Description   | Asynchronous processing                                  */
/*               |  function of SetEventStatusWithMonitorData.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      :                                       */
/*               | [in] Deque data Buffer                                   */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventWithMonitorData
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,   /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventStatusType , AUTOMATIC ) DequeStatus;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;

    DequeStatus = (Dem_EventStatusType)DataBuffPtr[DEM_DATABUF_EVENTSTATUS];/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_EVENTSTATUS */
    monitorData0 = (Dem_MonitorDataType)( (Dem_MonitorDataType)DataBuffPtr[DEM_DATABUF_MONITORDATA_0] |/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_0 */
                   ( (Dem_MonitorDataType)DataBuffPtr[DEM_DATABUF_MONITORDATA_1] << DEM_MONTORDATA_BITSHIFT_8 ) |/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_1 */
                   ( (Dem_MonitorDataType)DataBuffPtr[DEM_DATABUF_MONITORDATA_2] << DEM_MONTORDATA_BITSHIFT_16 ) |/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_2 */
                   ( (Dem_MonitorDataType)DataBuffPtr[DEM_DATABUF_MONITORDATA_3] << DEM_MONTORDATA_BITSHIFT_24 ) );/* [ARYCHK] DEM_ASYNCDATAQUE_MONITORDATA_ITEMSIZE / 1 / DEM_DATABUF_MONITORDATA_3 */

    retVal  =   Dem_Control_SetEventCommon( (Dem_u16_EventCtrlIndexType)Index, DequeStatus, monitorData0, (boolean)FALSE );

    return retVal;
}
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetEventStatusForUserDefinedMemoryProcess    */
/* Description   | Asynchronous processing function of                      */
/*               | SetEventFailedWithSyncFreezeFrameProcess.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      : Status of the event.                  */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventStatusForUserDefinedMemoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status, /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    eventId =   Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( (Dem_u16_EventCtrlIndexType)Index );
    monitorData0 = ( (Dem_MonitorDataType)eventId ) | DEM_MONITORDATA_SETEVENTSTATUS;

    retVal  =   Dem_UdmControl_SetEventCommon( (Dem_u16_EventCtrlIndexType)Index, ( Dem_EventStatusType )Status, monitorData0 );

    return retVal;
}
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */


/****************************************************************************/
/* Function Name | Dem_Control_CheckStatusForSetEvent_PrimaryMemory         */
/* Description   | Check event status.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus :                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetEvent_PrimaryMemory
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    switch( EventStatus )
    {
        case DEM_EVENT_STATUS_PASSED:
        case DEM_EVENT_STATUS_FAILED:
        case DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* Out of range */
            break;
    }

    return retVal;

}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_CheckStatusForSetEvent_UserDefMemory         */
/* Description   | Check event status.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus :                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetEvent_UserDefMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnv;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;

    retVal = DEM_IRT_NG;

    if ( ( EventStatus == DEM_EVENT_STATUS_PASSED ) || ( EventStatus == DEM_EVENT_STATUS_FAILED ) || ( EventStatus == DEM_EVENT_STATUS_FAILED_TO_PASSED ) )
    {
        retCnv  =   Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );  /* [GUD:RET:DEM_IRT_OK] udmEventIndex */

        if ( retCnv == DEM_IRT_OK )
        {
            /*  check memory type.      */
            memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByUdmEventIndex( udmEventIndex );

            if ( memType == DEM_MEMORYTYPE_ASYNCEVENT )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;

}

/****************************************************************************/
/* Function Name | Dem_Control_CheckStatusForSetFailedWithSyncFFD_UserDefMemory         */
/* Description   | Check event status.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus :                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusForSetFailedWithSyncFFD_UserDefMemory
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnv;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;

    retVal = DEM_IRT_NG;

    retCnv  =   Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );  /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
    if ( retCnv == DEM_IRT_OK )
    {
        /*  check memory type.      */
        memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByUdmEventIndex( udmEventIndex );        /* [GUD] udmEventIndex */

        if ( memType == DEM_MEMORYTYPE_SYNCEVENT )
        {
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;

}

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
