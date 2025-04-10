/* Dem_MonSts_c(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MonSts/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../usr/Dem_FiM_Connector.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "./Dem_MonStsTable.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Dem Mode */
#define DEM_MONITOR_STATUS_INVALID      ((Dem_MonitorStatusType)0xFFU)

/* For Set MonitorStatus processing in sync */
#define DEM_MONSTS_PASSED_BITMASK       ((Dem_MonitorStatusType)0xAEU)      /*  b10101110   */
#define DEM_MONSTS_FAILED_BITMASK       ((Dem_MonitorStatusType)0x8CU)      /*  b10001100   */
#define DEM_MONSTS_FAILED_BITSET        ((Dem_MonitorStatusType)0x23U)      /*  b00100011   */
#define DEM_MONSTS_INITILIZE_BITMASK    ((Dem_MonitorStatusType)0x8CU)      /*  b10001100   */
#define DEM_MONSTS_INITILIZE_BITSET     ((Dem_MonitorStatusType)0x50U)      /*  b01010000   */
#define DEM_MONSTS_NORMALIZE_BITMASK    ((Dem_MonitorStatusType)0xACU)      /*  b10101100   */

/* For Set MonitorStatus in async */
#define DEM_STATUSOFDTC_ASYNC_MASK              ((Dem_MonitorStatusType)0x8CU)      /*  b10001100   */
#define DEM_STATUSOFDTC_ASYNC_WITH_BIT5_MASK    ((Dem_MonitorStatusType)0xACU)      /*  b10101100   :   for Dem_StatusBitHandlingTestFailedSinceLastClear == TRUE   */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/*  bit7 is OFF MASK.   */
#define DEM_STATUSOFDTC_ASYNC_OUTPUT_MASK       ((Dem_MonitorStatusType)0x7FU)      /*  b01111111   */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )   */

/* For Process of recalculation */
typedef uint8        Dem_u08_MonStsRecalcProcType;               /*  MonitorStatus Recalc process type  */
#define DEM_RECALC_INITIALIZING         ((Dem_u08_MonStsRecalcProcType)0x00U)
#define DEM_RECALC_FIM_FIRST            ((Dem_u08_MonStsRecalcProcType)0x11U)
#define DEM_RECALC_FIM_PENDING          ((Dem_u08_MonStsRecalcProcType)0x22U)
#define DEM_RECALC_PRE_NOTIFY           ((Dem_u08_MonStsRecalcProcType)0x33U)
#define DEM_RECALC_NOTIFY               ((Dem_u08_MonStsRecalcProcType)0x44U)
#define DEM_RECALC_COMPLETE             ((Dem_u08_MonStsRecalcProcType)0x55U)
#define DEM_RECALC_NONE                 ((Dem_u08_MonStsRecalcProcType)0xFFU)

/* For Recalculate MonitorStatus */
/*------------------------------------------------------*/
/* typedef uint8        Dem_UdsStatusByteType           */
/*      #define                 bit pos     value       */
/*      DEM_UDS_STATUS_TF       bit0        0x01        */
/*      DEM_UDS_STATUS_TFTOC    bit1        0x02        */
/*      DEM_UDS_STATUS_PDTC     bit2        0x04        */
/*      DEM_UDS_STATUS_CDTC     bit3        0x08        */
/*      DEM_UDS_STATUS_TNCSLC   bit4        0x10        */
/*      DEM_UDS_STATUS_TFSLC    bit5        0x20        */
/*      DEM_UDS_STATUS_TNCTOC   bit6        0x40        */
/*      DEM_UDS_STATUS_WIR      bit7        0x80        */
/*------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_MonStsKindType, DEM_CODE ) Dem_MonSts_GetMonitorStatusKind
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind
);
static FUNC( void, DEM_CODE ) Dem_MonSts_SetSyncMonStsProc
(
    VAR( Dem_u08_MonStsKindType, AUTOMATIC ) MonStsKind,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForEventStatus
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
);
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForInitilize
(
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
);
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForNormalize
(
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcLoopForInit
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) LoopNum
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProcFimInit
(
    VAR( Dem_FiM_OpStatusType, AUTOMATIC ) OpStatusType,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProcNotify
(
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) LoopNum
);

static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_Initializing
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
);
static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_FiMFirst
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
);
static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_Notify
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
);

static FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatusUpdate
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_MonStsAsyncUpdModeType, AUTOMATIC ) AsyncUpdateMode
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_MonitorStatusType, DEM_VAR_NO_INIT )        Dem_MonitorStatus[ DEM_PRIMEM_EVENT_NUM ];

/* For Process of recalculation */
static VAR( Dem_u16_EventCtrlIndexType, DEM_VAR_NO_INIT )   Dem_IndexForInitMonitorStatus;
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT )  Dem_MonStsEventQueueReadIndex;
static VAR( Dem_u16_EventQueueIndexType, DEM_VAR_NO_INIT )  Dem_MonStsEventQueueReadCount;
static VAR( Dem_u08_MonStsRecalcProcType, DEM_VAR_NO_INIT ) Dem_ReCalcStatus;

static VAR( Dem_u08_MonStsAsyncUpdModeType, DEM_VAR_NO_INIT ) Dem_MonStsAsyncUpdMode;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_MonSts_Init                                          */
/* Description   | Init process of Dem_MonSts unit.                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_Init
(void)
{
    Dem_ReCalcStatus = DEM_RECALC_NONE;

    /* prepare for recomputation */
    Dem_MonSts_ReCalcStart( (boolean)TRUE );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_Shutdown                                      */
/* Description   | Shutdown process of Dem_MonSts unit.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_Shutdown
(void)
{
    /* Latch start */
    Dem_ModeMng_SetMode( DEM_MODE_UPDATE_ALL_MONITORSTATUS );

    Dem_ReCalcStatus = DEM_RECALC_NONE;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_GetMonitorStatus                              */
/* Description   | Get MonitorStatus                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/* Return Value  | Dem_MonitorStatusType                                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_MonitorStatusType, DEM_CODE ) Dem_MonSts_GetMonitorStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatus;

    monitorStatus   =   Dem_MonitorStatus[ EventCtrlIndex ];        /* [GUDCHK:CALLER]EventCtrlIndex */

    if ( monitorStatus != DEM_MONITOR_STATUS_INVALID )
    {
        monitorStatus   =   Dem_DTC_CnvDTCStatus_ForOutput( monitorStatus );
    }

    return monitorStatus;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_SetSyncMonitorStatus                          */
/* Description   | Set MonitorStatus in sync                                */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Kind : AsyncReq data kind                          */
/*               | [in]  EventCtrlIndex                                     */
/*               | [in]  EventStatus                                        */
/*               | [in]  DTCSettingStatus                                   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_SetSyncMonitorStatus
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) DTCSettingStatus
)
{
    VAR( Dem_ModeType, AUTOMATIC ) demMode;
    VAR( Dem_u08_MonStsKindType, AUTOMATIC ) monStsKind;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) setKind;

    monStsKind = Dem_MonSts_GetMonitorStatusKind( Kind );

    if( ( monStsKind == DEM_MONSTS_KIND_SET_EVENT_STATUS       )
     || ( monStsKind == DEM_MONSTS_KIND_INITILIZE_EVENT_STATUS )
     || ( monStsKind == DEM_MONSTS_KIND_NORMALIZE_EVENT_STATUS ) )
    {
        /* Require setting of MonitorStatus */
        demMode = Dem_ModeMng_GetMode();
        demMode = ( demMode & DEM_MODE_UPDATE_ALL_MONITORSTATUS );
        if( demMode != (Dem_ModeType)0U )
        {
            /* In the middle of latch */
            if( DTCSettingStatus != DEM_CTL_STS_DTC_SETTING_ENABLE )
            {
                /* Enqueue for event latch because don't enqueue in the middle of SID0x85 Disable */
                setKind = ( Kind | DEM_ASYNCREQ_MONSTS_MASK );
                (void)Dem_AsyncReq_Enqueue( setKind, (Dem_u16_AsyncReqItemAType)EventCtrlIndex, (Dem_u08_AsyncReqItemBType)EventStatus );          /* no return check required */
            }
        }
        else
        {
            /* Set MonitorStatus processing in sync */
            Dem_MonSts_SetSyncMonStsProc( monStsKind, EventCtrlIndex, EventStatus );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_UpdateAllMonitorStatus                        */
/* Description   | Update All MonitorStatus                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_UpdateAllMonitorStatus
(void)
{
    /* Latch start */
    Dem_ModeMng_SetMode( DEM_MODE_UPDATE_ALL_MONITORSTATUS );

    return;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_SetAsyncMonitorStatus_OnOverflow_InEvtStrgGrp */
/* Description   | Set MonitorStatus in async                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | void                                                     */
/* Notes         | set MonitorStatus of bit2,3,7                            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatus_OnOverflow_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         */

    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  asyncmonitor status     */
        Dem_MonSts_SetAsyncMonitorStatusUpdate( eventCtrlIndex, DEM_MONSTS_ASYNCUPD_OVERFLOW );

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_SetAsyncMonitorStatus                         */
/* Description   | Set MonitorStatus in async                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/* Return Value  | void                                                     */
/* Notes         | set MonitorStatus of bit2,3,7                            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatus
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    Dem_MonSts_SetAsyncMonitorStatusUpdate( EventCtrlIndex, Dem_MonStsAsyncUpdMode );
    return ;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_SetAsyncUpdateMode                            */
/* Description   | Set update MonitorStatus mode in async                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  AsyncUpdateMode                                    */
/*               |          DEM_MONSTS_ASYNCUPD_NORMAL                      */
/*               |          DEM_MONSTS_ASYNCUPD_OVERFLOW                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncUpdateMode
(
    VAR( Dem_u08_MonStsAsyncUpdModeType, AUTOMATIC ) AsyncUpdateMode
)
{
    Dem_MonStsAsyncUpdMode  =   AsyncUpdateMode;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_SetAsyncMonitorStatusUpdate                   */
/* Description   | Set MonitorStatus in async                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               | [in]  AsyncUpdateMode                                    */
/*               |          DEM_MONSTS_ASYNCUPD_NORMAL                      */
/*               |              : no overflow.(setevent/aging etc.          */
/*               |          DEM_MONSTS_ASYNCUPD_OVERFLOW                    */
/*               |              : overflow.                                 */
/* Return Value  | void                                                     */
/* Notes         | set MonitorStatus of bit2,3,7                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MonSts_SetAsyncMonitorStatusUpdate
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_MonStsAsyncUpdModeType, AUTOMATIC ) AsyncUpdateMode
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) baseStatusOfDTC;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) oldMonitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) baseMonitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) newMonitorStatus;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEventId;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) asyncResetBitMask;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;


    resultGetEventId = Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId );                            /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */
    if( resultGetEventId == DEM_IRT_OK )
    {
        /*  reset bit5 with bit3 off or not.        */
        resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

        SchM_Enter_Dem_MonitorStatus();                                                                     /* exclusion control start */

        /*  get monitor status      */
        oldMonitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                                                         /* [GUD]EventCtrlIndex */

        /*  get current statusOfDTC         */
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                            /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );                                   /* no return check required */

        if (( AsyncUpdateMode == DEM_MONSTS_ASYNCUPD_NORMAL )
         || ( AsyncUpdateMode == DEM_MONSTS_ASYNCUPD_AGING  ))
        {
            /*------------------------------*/
            /*  not Overflow.               */
            /*------------------------------*/
            if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
            {
                /*------------------------------------------------------------------------------*/
                /*  bit5 OFF at Aging.                                                          */
                /*------------------------------------------------------------------------------*/
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
                /*------------------------------------------------------------------------------*/
                /*  reset monitor status with bit5.             */
                asyncResetBitMask   =   DEM_STATUSOFDTC_ASYNC_WITH_BIT5_MASK;
            }
            else
            {
                /*----------------------------------------------------------------------*/
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
                /*----------------------------------------------------------------------*/
                /*  monitor status reset mask : reset bit2,3,7      */
                asyncResetBitMask   =   DEM_STATUSOFDTC_ASYNC_MASK;
            }
        }
        else
        {
            /*------------------------------*/
            /*  at Overflow.                */
            /*------------------------------*/
            if (( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
             || ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT ) )
            {
                /*------------------------------------------------------------------------------*/
                /*  bit5 OFF on Overflow.                                                       */
                /*------------------------------------------------------------------------------*/
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT             */
                /*------------------------------------------------------------------------------*/
                /*  reset monitor status with bit5.             */
                asyncResetBitMask   =   DEM_STATUSOFDTC_ASYNC_WITH_BIT5_MASK;
            }
            else
            {
                /*----------------------------------------------------------------------*/
                /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
                /*----------------------------------------------------------------------*/
                /*  monitor status reset mask : reset bit2,3,7      */
                asyncResetBitMask   =   DEM_STATUSOFDTC_ASYNC_MASK;
            }
        }


        /* Resets Monitor status bit2,3,7, and with/without bit5 */
        baseMonitorStatus   = ( oldMonitorStatus & (~asyncResetBitMask) );                      /* Get bit 0,1,4,6(,5:config FALSE)       */
        baseStatusOfDTC     = ( (Dem_MonitorStatusType)statusOfDTC & asyncResetBitMask );       /* Get bit 2,3,7(,5:config TRUE)          */

        newMonitorStatus    = ( baseMonitorStatus | baseStatusOfDTC );     /*  merge sync bit from monitorstatus(0,1,4,5,6) and async bit from statusOfDTC(2,3,7)  */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
        if ( newMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            newMonitorStatus    = ( newMonitorStatus & DEM_STATUSOFDTC_ASYNC_OUTPUT_MASK );         /* output mask.                            */
        }
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )   */

        /*  set new monitor status      */
        Dem_MonitorStatus[ EventCtrlIndex ] = newMonitorStatus;                                                 /* Update MonitorStatus */      /* [GUD]EventCtrlIndex */
        SchM_Exit_Dem_MonitorStatus();                                                                      /* exclusion control stop */

        /*  if MonitorStatus is not DEM_MONITOR_STATUS_INVALID, convert monitor status .    */
        if ( oldMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            oldMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( oldMonitorStatus );
        }
        if ( newMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            newMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( newMonitorStatus );
        }

        /* Notify FiM of MonitorStatus */
        if( oldMonitorStatus != newMonitorStatus )
        {
            Dem_FiM_DemTriggerOnMonitorStatus( eventId, oldMonitorStatus, newMonitorStatus );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcForOC                                   */
/* Description   | Recalculate MonitorStatus for OC                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/* Parameters    | [in]  FailureCycleFlag                                   */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcForOC
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatusNew;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatusMask;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) statusOfDTCMask;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) resetTestFailedBit;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    SchM_Enter_Dem_MonitorStatus();                                         /* exclusion control start */

    /* Recalculate MonitorStatus */
    monitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                    /* [GUDCHK:CALLER]EventCtrlIndex */

    if( monitorStatus != DEM_MONITOR_STATUS_INVALID )
    {
        /* Get statusOfDTC */
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );                   /* no return check required */

        /*------------------------------------------*/
        /*  config information                      */
        /*------------------------------------------*/
        /*  reset bit0 at OperationCycle restart.   */
        if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF ) == DEM_OPCYCUPD_FLCYC_INITIALVALUE )
        {
            /*--------------------------------------------------*/
            /*  DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF :   OFF         */
            /*--------------------------------------------------*/
            /*  monitorStatus mask : bit0                   */
            monitorStatusMask   =   DEM_UDS_STATUS_TF;
        }
        else
        {
            /*--------------------------------------------------*/
            /*  DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF :   ON          */
            /*--------------------------------------------------*/
            resetTestFailedBit  =   Dem_ResetTestFailedAtOpCycRestart;
            if ( resetTestFailedBit == (boolean)TRUE )
            {
                /*  monitorStatus mask : none.                  */
                monitorStatusMask   =   DEM_DTCSTATUS_BYTE_ALL_OFF;
            }
            else
            {
                /*  monitorStatus mask : bit0                   */
                monitorStatusMask   =   DEM_UDS_STATUS_TF;
            }
        }

        /*  reset bit1/6 at OperationCycle restart.   */
        if (( FailureCycleFlag & ( DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC ) ) == DEM_OPCYCUPD_FLCYC_INITIALVALUE )
        {
            /*--------------------------------------------------*/
            /*  DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC  :   OFF     */
            /*  DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC :   OFF     */
            /*--------------------------------------------------*/
            /*  monitorStatus mask : bit1 / 6                   */
            monitorStatusMask   =   monitorStatusMask | ( DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TNCTOC );
        }

        /*------------------------------------------*/
        /*  config information                      */
        /*------------------------------------------*/
        /*  reset bit5 with bit3 off or not.        */
        resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

        if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
        {
            /*------------------------------------------------------------------------------*/
            /*  bit5 OFF at Aging.                                                          */
            /*------------------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
            /*------------------------------------------------------------------------------*/
            /*  monitorStatus mask : bit4                   */
            monitorStatusMask       =   ( monitorStatusMask | DEM_UDS_STATUS_TNCSLC );

            /*  statusOfDTC mask   : bit2,3,7 + bit5        */
            statusOfDTCMask         =   ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_WIR | DEM_UDS_STATUS_TFSLC );
        }
        else
        {
            /*----------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_NORMAL           */
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT     */
            /*----------------------------------------------------------------------*/
            /*  monitorStatus mask : bit4, 5                */
            monitorStatusMask       =   ( monitorStatusMask | DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TFSLC );

            /*  statusOfDTC mask   : bit2,3,7               */
            statusOfDTCMask         =   ( DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_WIR );
        }

        /*----------------------------------*/
        /*  calcurate new monitor status.   */
        /*----------------------------------*/
        monitorStatusNew    =   ( monitorStatus & monitorStatusMask );
        monitorStatusNew    =   monitorStatusNew | ( statusOfDTC & statusOfDTCMask );

        /*  bit1,6 at OperationCycle restart    */
        if (( FailureCycleFlag & DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC ) == DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC )
        {
            monitorStatusNew    =   ( monitorStatusNew | DEM_UDS_STATUS_TNCTOC );   /*  bit6    */
        }
        Dem_MonitorStatus[ EventCtrlIndex ] = monitorStatusNew;             /* [GUDCHK:CALLER]EventCtrlIndex */
    }

    SchM_Exit_Dem_MonitorStatus();                                          /* exclusion control stop */

    return;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcForClearDTC                             */
/* Description   | Recalculate MonitorStatus for clearDTC                   */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcForClearDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  *//* [GUDCHK:CALLER]EventStrgIndex */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndex );    /*  get Delegate EventCtrlIndex                         *//* [GUDCHK:CALLER]EventStrgIndex */

    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        SchM_Enter_Dem_MonitorStatus();                                         /* exclusion control start */

        monitorStatus = Dem_MonitorStatus[ eventCtrlIndex ];                                                                /* [GUDCHK:CALLER]EventStrgIndex */
        if( monitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            Dem_MonitorStatus[ eventCtrlIndex ] = ( DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC );    /*  bit4,6      */  /* [GUDCHK:CALLER]EventStrgIndex */
        }

        SchM_Exit_Dem_MonitorStatus();                                          /* exclusion control stop */

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );                                /* [GUDCHK:CALLER]EventStrgIndex */
    }


    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcStart                                   */
/* Description   | prepare for recalculation                                */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReCalcFlg                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_ReCalcStart
(
    VAR( boolean, AUTOMATIC ) ReCalcFlg
)
{
    Dem_IndexForInitMonitorStatus = (Dem_u16_EventCtrlIndexType)0U;
    Dem_MonStsEventQueueReadIndex = (Dem_u16_EventQueueIndexType)0U;
    Dem_MonStsEventQueueReadCount = (Dem_u16_EventQueueIndexType)0U;
    Dem_ReCalcStatus = DEM_RECALC_INITIALIZING;
    if( ReCalcFlg == (boolean)FALSE )
    {
        Dem_ReCalcStatus = DEM_RECALC_PRE_NOTIFY;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProc                                    */
/* Description   | Process of recalculation                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  InitType : Process Type                            */
/*               |         DEM_MONSTS_RECALC_TYPE_INIT                      */
/*               |         DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE            */
/*               |         DEM_MONSTS_RECALC_TYPE_DTC_CLEAR                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_NG                                       */
/*               |         DEM_IRT_OK                                       */
/*               |         DEM_IRT_PENDING                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProc
(
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) reCalcStatus;

    retVal = DEM_IRT_NG;
    reCalcStatus = Dem_ReCalcStatus;

    switch( InitType )
    {
        case DEM_MONSTS_RECALC_TYPE_INIT:
        case DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE:
        case DEM_MONSTS_RECALC_TYPE_DTC_CLEAR:
            retVal = DEM_IRT_PENDING;
            break;

        default:
            /* No process */
            break;
    }

    if( retVal == DEM_IRT_PENDING )
    {
        /* Initialize MonitorStatus */
        reCalcStatus    =   Dem_MonSts_ReCalcProcMode_Initializing( reCalcStatus, InitType );

        /* FiM_DemInit */
        reCalcStatus    =   Dem_MonSts_ReCalcProcMode_FiMFirst( reCalcStatus, InitType );

        /* Notify FiM of latch event */
        reCalcStatus    =   Dem_MonSts_ReCalcProcMode_Notify( reCalcStatus, InitType );

        /* Process of recalculation complete */
        if( reCalcStatus == DEM_RECALC_COMPLETE )
        {
            reCalcStatus = DEM_RECALC_NONE;
            retVal = DEM_IRT_OK;
        }
    }

    Dem_ReCalcStatus = reCalcStatus;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProcMode_Initializing                   */
/* Description   | Process of recalculation : Initialize MonitorStatus      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReCalcStatus : ReCalcuration status.               */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/*               | [in]  InitType : Process Type                            */
/*               |         DEM_MONSTS_RECALC_TYPE_INIT                      */
/*               |         DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE            */
/*               |         DEM_MONSTS_RECALC_TYPE_DTC_CLEAR                 */
/* Return Value  | Dem_u08_MonStsRecalcProcType                             */
/*               |       Next ReCalcuration status.                         */
/*               |         DEM_RECALC_INITIALIZING                          */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_Initializing
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultProc;
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) reCalcStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventNumForFiMInitProcess;

    reCalcStatus    =   ReCalcStatus;

    if( reCalcStatus == DEM_RECALC_INITIALIZING )
    {
        resultProc = DEM_IRT_OK;
        if( InitType == DEM_MONSTS_RECALC_TYPE_INIT )
        {
            eventNumForFiMInitProcess = Dem_EventNumForFiMInitProcess;
            resultProc = Dem_MonSts_ReCalcLoopForInit( eventNumForFiMInitProcess );
        }

        if( resultProc != DEM_IRT_PENDING )
        {
            reCalcStatus = DEM_RECALC_FIM_FIRST;
        }
    }
    return reCalcStatus;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProcMode_FiMFirst                       */
/* Description   | Process of recalculation : FiM_DemInit process.          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReCalcStatus : ReCalcuration status.               */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/*               | [in]  InitType : Process Type                            */
/*               |         DEM_MONSTS_RECALC_TYPE_INIT                      */
/*               |         DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE            */
/*               |         DEM_MONSTS_RECALC_TYPE_DTC_CLEAR                 */
/* Return Value  | Dem_u08_MonStsRecalcProcType                             */
/*               |       Next ReCalcuration status.                         */
/*               |         DEM_RECALC_INITIALIZING                          */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_FiMFirst
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultProc;
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) reCalcStatus;

    reCalcStatus    =   ReCalcStatus;

    /* FiM_DemInit */
    if( reCalcStatus == DEM_RECALC_FIM_FIRST )
    {
        /* FiM_DemInit(Initial) */
        resultProc = Dem_MonSts_ReCalcProcFimInit( DEM_FIM_OPSTATUS_INITIAL, InitType );
        reCalcStatus = DEM_RECALC_FIM_PENDING;
        if( resultProc != DEM_IRT_PENDING )
        {
            reCalcStatus = DEM_RECALC_PRE_NOTIFY;
        }
    }
    else if( reCalcStatus == DEM_RECALC_FIM_PENDING )
    {
        /* FiM_DemInit(Pending) */
        resultProc = Dem_MonSts_ReCalcProcFimInit( DEM_FIM_OPSTATUS_PENDING, InitType );
        if( resultProc != DEM_IRT_PENDING )
        {
            reCalcStatus = DEM_RECALC_PRE_NOTIFY;
        }
    }
    else
    {
        /* No process */
    }

    return reCalcStatus;
}

/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProcMode_Notify                         */
/* Description   | Process of recalculation : Notify FiM of latch event.    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  ReCalcStatus : ReCalcuration status.               */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/*               | [in]  InitType : Process Type                            */
/*               |         DEM_MONSTS_RECALC_TYPE_INIT                      */
/*               |         DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE            */
/*               |         DEM_MONSTS_RECALC_TYPE_DTC_CLEAR                 */
/* Return Value  | Dem_u08_MonStsRecalcProcType                             */
/*               |       Next ReCalcuration status.                         */
/*               |         DEM_RECALC_INITIALIZING                          */
/*               |         DEM_RECALC_FIM_FIRST                             */
/*               |         DEM_RECALC_FIM_PENDING                           */
/*               |         DEM_RECALC_PRE_NOTIFY                            */
/*               |         DEM_RECALC_NOTIFY                                */
/*               |         DEM_RECALC_COMPLETE                              */
/*               |         DEM_RECALC_NONE                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_MonStsRecalcProcType, DEM_CODE ) Dem_MonSts_ReCalcProcMode_Notify
(
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) ReCalcStatus,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultProc;
    VAR( Dem_u08_MonStsRecalcProcType, AUTOMATIC ) reCalcStatus;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) recalculateEventNumForFiMInitProcess;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) recalculateEventNumForFiMMainProcess;

    reCalcStatus    =   ReCalcStatus;

    if( reCalcStatus == DEM_RECALC_PRE_NOTIFY )
    {
        reCalcStatus = DEM_RECALC_NOTIFY;
        Dem_MonStsEventQueueReadIndex = Dem_AsyncReq_GetReadIndex();
        Dem_MonStsEventQueueReadCount = (Dem_u16_EventQueueIndexType)0U;
    }

    /* Notify FiM of latch event */
    if( reCalcStatus == DEM_RECALC_NOTIFY )
    {
        if( InitType == DEM_MONSTS_RECALC_TYPE_INIT )
        {
            recalculateEventNumForFiMInitProcess = Dem_RecalculateEventNumForFiMInitProcess;
            resultProc = Dem_MonSts_ReCalcProcNotify( recalculateEventNumForFiMInitProcess );
        }
        else
        {
            recalculateEventNumForFiMMainProcess = Dem_RecalculateEventNumForFiMMainProcess;
            resultProc = Dem_MonSts_ReCalcProcNotify( recalculateEventNumForFiMMainProcess );
        }

        if( resultProc != DEM_IRT_PENDING )
        {
            reCalcStatus = DEM_RECALC_COMPLETE;
        }
    }
    return reCalcStatus;
}

#if ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MonSts_NotifyEventAvailable                          */
/* Description   | Notify FiM of EventAvailable                             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               | [in]  AvailableStatus                                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MonSts_NotifyEventAvailable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) oldMonitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) newMonitorStatus;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEventId;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    resultGetEventId = Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId );                            /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

    if( resultGetEventId == DEM_IRT_OK )
    {
        statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                            /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
        (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );       /* no return check required */

        SchM_Enter_Dem_MonitorStatus();                                         /* exclusion control start */
        oldMonitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                                                         /* [GUD]EventCtrlIndex */
        newMonitorStatus = oldMonitorStatus;

        if( AvailableStatus == (boolean)FALSE )
        {
            /* Set event available */
            newMonitorStatus = DEM_MONITOR_STATUS_INVALID;
        }
        else
        {
            /* Set event unavailable */
            if( oldMonitorStatus == DEM_MONITOR_STATUS_INVALID )
            {
                newMonitorStatus = (Dem_MonitorStatusType)statusOfDTC;
            }
            else
            {
                /* No process because Notified FiM in Dem_MonSts_SetSyncMonitorStatusProc() */
            }
        }
        Dem_MonitorStatus[ EventCtrlIndex ] = newMonitorStatus;                     /* Update MonitorStatus */          /* [GUD]EventCtrlIndex */
        SchM_Exit_Dem_MonitorStatus();                                          /* exclusion control stop */

        /*  if MonitorStatus is not DEM_MONITOR_STATUS_INVALID, convert monitor status .    */
        if ( oldMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            oldMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( oldMonitorStatus );
        }
        if ( newMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            newMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( newMonitorStatus );
        }

        /* Notify FiM of MonitorStatus */
        if( oldMonitorStatus != newMonitorStatus )
        {
            Dem_FiM_DemTriggerOnMonitorStatus( eventId, oldMonitorStatus, newMonitorStatus );
        }
    }

    return;
}
#endif  /* ( DEM_EVENT_AVAILABILITY_FIM_REPORT == STD_ON ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_MonSts_GetMonitorStatusKind                          */
/* Description   | Get kind of MonitorStatus                                */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Kind : AsyncReq data kind                          */
/* Return Value  | Dem_u08_MonStsKindType                                   */
/*               |         DEM_MONSTS_KIND_NONE                             */
/*               |         DEM_MONSTS_KIND_SET_EVENT_STATUS                 */
/*               |         DEM_MONSTS_KIND_INITILIZE_EVENT_STATUS           */
/*               |         DEM_MONSTS_KIND_NORMALIZE_EVENT_STATUS           */
/*               |         DEM_MONSTS_KIND_UPDATE_ALL                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_MonStsKindType, DEM_CODE ) Dem_MonSts_GetMonitorStatusKind
(
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) Kind
)
{
    VAR( Dem_u08_MonStsKindType, AUTOMATIC ) monStsKind;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqNum;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) asyncReqIndex;

    monStsKind = DEM_MONSTS_KIND_NONE;
    asyncReqNum = Dem_AsyncReqNum;
    asyncReqIndex = (Dem_u08_AsyncReqTableIndexType)Kind;

    if( asyncReqIndex < asyncReqNum )                               /* [GUD:if]asyncReqIndex */
    {
        monStsKind = Dem_MonitorStatusKindTable[ asyncReqIndex ];   /* [GUD]asyncReqIndex */
    }

    return monStsKind;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_SetSyncMonStsProc                             */
/* Description   | Set MonitorStatus processing in sync                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]  MonStsKind                                         */
/*               | [in]  EventCtrlIndex                                     */
/*               | [in]  EventStatus                                        */
/* Return Value  | void                                                     */
/* Notes         | set MonitorStatus of bit0,1,4,5,6                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MonSts_SetSyncMonStsProc
(
    VAR( Dem_u08_MonStsKindType, AUTOMATIC ) MonStsKind,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEventId;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) baseMonitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) oldMonitorStatus;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) newMonitorStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    resultGetEventId = Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId );                                /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

    if( resultGetEventId == DEM_IRT_OK )
    {
        SchM_Enter_Dem_MonitorStatus();                                                 /* exclusion control start */
        oldMonitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                                                             /* [GUD]EventCtrlIndex */
        newMonitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                                                             /* [GUD]EventCtrlIndex */

        /* Set MonitorStatus for Calculation */
        baseMonitorStatus = Dem_MonitorStatus[ EventCtrlIndex ];                                                            /* [GUD]EventCtrlIndex */
        if( baseMonitorStatus == DEM_MONITOR_STATUS_INVALID )
        {
            /* Set baseMonitorStatus in statusOfDTC because do not notify FiM in Dem_MonSts_NotifyEventAvailable() */
            statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                            /* [GUD]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
            (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );           /* no return check required */
            baseMonitorStatus = (Dem_MonitorStatusType)statusOfDTC;
        }

        /* calculate MonitorStatus */
        switch( MonStsKind )
        {
            /* For set event status */
            case DEM_MONSTS_KIND_SET_EVENT_STATUS:
                Dem_MonSts_CalcSyncMonStsForEventStatus( EventStatus, baseMonitorStatus, &newMonitorStatus );
                break;

            /* For initilize event status */
            case DEM_MONSTS_KIND_INITILIZE_EVENT_STATUS:
                Dem_MonSts_CalcSyncMonStsForInitilize( baseMonitorStatus, &newMonitorStatus );
                break;

            /* For normalize event status */
            case DEM_MONSTS_KIND_NORMALIZE_EVENT_STATUS:
                Dem_MonSts_CalcSyncMonStsForNormalize( baseMonitorStatus, &newMonitorStatus );
                break;

            default:
                /* No process */
                break;
        }

        Dem_MonitorStatus[ EventCtrlIndex ] = newMonitorStatus;                             /* Update MonitorStatus */      /* [GUD]EventCtrlIndex */
        SchM_Exit_Dem_MonitorStatus();                                                  /* exclusion control stop */

        /*  if MonitorStatus is not DEM_MONITOR_STATUS_INVALID, convert monitor status .    */
        if ( oldMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            oldMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( oldMonitorStatus );
        }
        if ( newMonitorStatus != DEM_MONITOR_STATUS_INVALID )
        {
            newMonitorStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( newMonitorStatus );
        }

        /* Notify FiM of MonitorStatus */
        if( oldMonitorStatus != newMonitorStatus )
        {
            Dem_FiM_DemTriggerOnMonitorStatus( eventId, oldMonitorStatus, newMonitorStatus );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_CalcSyncMonStsForEventStatus                  */
/* Description   | calculate MonitorStatus for set event status             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStatus                                        */
/*               | [in]  BaseMonitorStatus                                  */
/*               | [out] NewMonitorStatusPtr                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForEventStatus
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) calMonitorStatus;

    if( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        calMonitorStatus = ( BaseMonitorStatus & DEM_MONSTS_PASSED_BITMASK );
        (*NewMonitorStatusPtr) = calMonitorStatus;
    }
    else if( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        calMonitorStatus = ( BaseMonitorStatus & DEM_MONSTS_FAILED_BITMASK );
        calMonitorStatus |= DEM_MONSTS_FAILED_BITSET;
        (*NewMonitorStatusPtr) = calMonitorStatus;
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_CalcSyncMonStsForInitilize                    */
/* Description   | calculate MonitorStatus for initilize event status       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  BaseMonitorStatus                                  */
/*               | [out] NewMonitorStatusPtr                                */
/* Return Value  | Dem_MonitorStatusType                                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForInitilize
(
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) calMonitorStatus;

    calMonitorStatus = ( BaseMonitorStatus & DEM_MONSTS_INITILIZE_BITMASK );
    calMonitorStatus |= DEM_MONSTS_INITILIZE_BITSET;
    (*NewMonitorStatusPtr) = calMonitorStatus;

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_CalcSyncMonStsForNormalize                    */
/* Description   | calculate MonitorStatus for normalize event status       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  BaseMonitorStatus                                  */
/*               | [out] NewMonitorStatusPtr                                */
/* Return Value  | Dem_MonitorStatusType                                    */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MonSts_CalcSyncMonStsForNormalize
(
    VAR( Dem_MonitorStatusType, AUTOMATIC ) BaseMonitorStatus,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) NewMonitorStatusPtr
)
{
    VAR( Dem_MonitorStatusType, AUTOMATIC ) calMonitorStatus;

    calMonitorStatus = ( BaseMonitorStatus & DEM_MONSTS_NORMALIZE_BITMASK );
    (*NewMonitorStatusPtr) = calMonitorStatus;

    return;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcLoopForInit                             */
/* Description   | Recalculate MonitorStatus for init                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  LoopNum                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK                                         */
/*               |       DEM_IRT_PENDING                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcLoopForInit
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) LoopNum
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) loopCounter;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )  retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    retVal = DEM_IRT_OK;
    eventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    eventCtrlIndex = Dem_IndexForInitMonitorStatus;

    for( loopCounter = (Dem_u16_EventCtrlIndexType)0U; loopCounter < LoopNum; loopCounter++ )
    {
        if( eventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]eventCtrlIndex */
        {
            /* Recalculate MonitorStatus */
            monitorStatus = DEM_MONITOR_STATUS_INVALID;
            availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );                                      /* [GUD]eventCtrlIndex */
            if( availableStatus == (boolean)TRUE )
            {
                statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &statusOfDTC );                   /* no return check required */
                monitorStatus = (Dem_MonitorStatusType)statusOfDTC;
            }
            Dem_MonitorStatus[ eventCtrlIndex ] = monitorStatus;                                            /* [GUD]eventCtrlIndex */

            eventCtrlIndex++;
        }
        else
        {
            break;
        }
    }

    if( eventCtrlIndex < eventConfigureNum )                                                                /* [GUD:if]eventCtrlIndex */
    {
        retVal = DEM_IRT_PENDING;
    }

    Dem_IndexForInitMonitorStatus = eventCtrlIndex;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProcFimInit                             */
/* Description   | FiM_DemInit in Process of recalculation                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]  OpStatusType                                       */
/*               |         DEM_FIM_OPSTATUS_INITIAL                         */
/*               |         DEM_FIM_OPSTATUS_PENDING                         */
/*               | [in]  InitType                                           */
/*               |         DEM_MONSTS_RECALC_TYPE_INIT                      */
/*               |         DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE            */
/*               |         DEM_MONSTS_RECALC_TYPE_DTC_CLEAR                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_OK                                       */
/*               |         DEM_IRT_NG                                       */
/*               |         DEM_IRT_PENDING                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProcFimInit
(
    VAR( Dem_FiM_OpStatusType, AUTOMATIC ) OpStatusType,
    VAR( Dem_u08_MonStsReCalcType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Std_ReturnType, AUTOMATIC )             resultFimDemInit;
    VAR( Dem_FiM_DemInitTriggerType, AUTOMATIC ) triggerType;

    retVal = DEM_IRT_PENDING;
    switch( InitType )
    {
        case DEM_MONSTS_RECALC_TYPE_INIT:
            triggerType = DEM_FIM_INITMODE_DEMINIT;
            break;

        case DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE:
            triggerType = DEM_FIM_INITMODE_OPERATIONCYCLE_ONLY;
            break;

        case DEM_MONSTS_RECALC_TYPE_DTC_CLEAR:
            triggerType = DEM_FIM_INITMODE_DTC_CLEAR;
            break;

        default:
            retVal = DEM_IRT_NG;
            break;
    }

    if( retVal == DEM_IRT_PENDING )
    {
        resultFimDemInit = Dem_FiM_DemInit( OpStatusType, triggerType );
        if( resultFimDemInit != DEM_FIM_E_PENDING )
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MonSts_ReCalcProcNotify                              */
/* Description   | Notify FiM of latch event in Process of recalculation    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  LoopNum                                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_OK                                       */
/*               |         DEM_IRT_PENDING                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MonSts_ReCalcProcNotify
(
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) LoopNum
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) count;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) readIndex;
    VAR( Dem_u16_EventQueueIndexType, AUTOMATIC ) readCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetQueue;
    VAR( Dem_EventStatusType, AUTOMATIC ) eventStatus;
    VAR( Dem_u08_AsyncReqTableIndexType, AUTOMATIC ) kind;
    VAR( Dem_u08_MonStsKindType, AUTOMATIC ) monStsKind;
    VAR( boolean, AUTOMATIC ) loopFinFlg;

    retVal = DEM_IRT_PENDING;
    readIndex = Dem_MonStsEventQueueReadIndex;
    readCount = Dem_MonStsEventQueueReadCount;
    loopFinFlg = (boolean)FALSE;

    for( count = (Dem_u16_EventQueueIndexType)0U; count < LoopNum; count++ )
    {
        SchM_Enter_Dem_EventQueueBufferAccess();                            /* exclusion control start */
        /* Check Queue */
        resultGetQueue = Dem_AsyncReq_CheckQueueNext( &readIndex, &readCount, &kind, &eventCtrlIndex, &eventStatus );
        if( resultGetQueue != DEM_IRT_OK )
        {
            /* No Queue */
            loopFinFlg = (boolean)TRUE;
            Dem_ModeMng_ClearMode( DEM_MODE_UPDATE_ALL_MONITORSTATUS );
        }
        SchM_Exit_Dem_EventQueueBufferAccess();                             /* exclusion control stop */

        if( resultGetQueue == DEM_IRT_OK )
        {
            kind = ( kind & (Dem_u08_AsyncReqTableIndexType)(~DEM_ASYNCREQ_MONSTS_MASK) );           /* clear MonitorStatus of bit7 */
            monStsKind = Dem_MonSts_GetMonitorStatusKind( kind );

            switch( monStsKind )
            {
                case DEM_MONSTS_KIND_SET_EVENT_STATUS:
                case DEM_MONSTS_KIND_INITILIZE_EVENT_STATUS:
                case DEM_MONSTS_KIND_NORMALIZE_EVENT_STATUS:
                    Dem_MonSts_SetSyncMonStsProc( monStsKind, eventCtrlIndex, eventStatus );
                    break;

                case DEM_MONSTS_KIND_UPDATE_ALL:
                    loopFinFlg = (boolean)TRUE;
                    break;

                default:
                    /* No process */
                    break;
            }
        }

        if( loopFinFlg == (boolean)TRUE )
        {
            retVal = DEM_IRT_OK;
            break;
        }
    }

    Dem_MonStsEventQueueReadIndex = readIndex;
    Dem_MonStsEventQueueReadCount = readCount;

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
