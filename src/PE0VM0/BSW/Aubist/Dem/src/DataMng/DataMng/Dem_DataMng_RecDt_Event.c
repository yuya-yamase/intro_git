/* Dem_DataMng_RecDt_Event_c(v5-9-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_Event_c/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "MisfireMng/Dem_MisfireMng_local.h"
#include "Dem_DataMng_local.h"
#include "Dem_DataMng_GetRecordData.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Rc_MisfireMng.h"
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Rc_SimilarMng.h"
#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */
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
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_DataMng_InitEventRecord_Ctl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventCtlRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) DestEventRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_DataMng_SetEventCtlRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMngM_GetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecord_Ctl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordType, AUTOMATIC, AUTOMATIC ) DestEventRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecord_MM
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordType, AUTOMATIC, AUTOMATIC ) DestEventRecordPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckEventRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_DataMng_InitSavedZoneOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_EventMng_InitMirrorMemory
( void );
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_EventMng_InitRecord_Padding
(
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) EventRecordPtr
);
#endif /* DEM_EVENT_RECORD_PADDING_EXIST -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_EventNvMStatus[DEM_EVENT_RECORD_LIST_NUM];
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_EventRecordType, DEM_VAR_NO_INIT ) Dem_TmpEventMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_EventRecordType, DEM_VAR_SAVED_ZONE ) Dem_EventRecordList[DEM_EVENT_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetEventRecord                              */
/* Description   | Gets the data body of the event record from the event r- */
/*               | ecord list corresponding to the specified event index. - */
/*               | (for Dem_DataCtl subunit)                                */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/*               |                    &Dem_TmpDisabledRecord.EventRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.EventRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_DataMng_GetEventCtlRecord( EventStrgIndex, EventRecordPtr );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_FaultIndex                            */
/* Description   | Gets the fault index of the event record list correspon- */
/*               | ding to the specified event index.                       */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] FaultIndexPtr :                                    */
/*               |        The pointer of the fault index.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_FaultIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                      /* [GUD:if]EventStrgIndex */
    {
        *FaultIndexPtr = Dem_EventRecordList[EventStrgIndex].FaultIndex;        /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_StatusOfDTC                           */
/* Description   | Gets the status of DTC of the event record list corresp- */
/*               | onding to the specified event index.                     */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        The pointer of the status of DTC.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_StatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *StatusOfDTCPtr = Dem_EventRecordList[EventStrgIndex].StatusOfDTC;                                  /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_ExtendDTCStatus                       */
/* Description   | Gets the Extend status of DTC of the event record list   */
/*               | corresponding to the specified event index.              */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] ExtendStatusOfDTCPtr :                             */
/*               |        The pointer of the status of DTC.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_ExtendDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_DTCStatusExType, AUTOMATIC, AUTOMATIC ) ExtendStatusOfDTCPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *ExtendStatusOfDTCPtr = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC;                      /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_DTCStatusAndExtendDTCStatus           */
/* Description   | Gets the Extend status of DTC of the event record list   */
/*               | corresponding to the specified event index.              */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] ExtendStatusOfDTC2Ptr :                            */
/*               |        The pointer of the status of DTC.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_ExtendDTCStatus2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC, AUTOMATIC ) ExtendStatusOfDTC2Ptr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *ExtendStatusOfDTC2Ptr = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2;                    /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_DTCStatusSt                           */
/* Description   | Gets the Extend status of DTC of the event record list   */
/*               | corresponding to the specified event index.              */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] DTCStatusStPtr :                                   */
/*               |        The pointer of the status of DTC.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_GetER_ExtendDTCStatus2.*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_DTCStatusSt
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        DTCStatusStPtr->DTCStatus        = Dem_EventRecordList[EventStrgIndex].StatusOfDTC;                         /* [GUD]EventStrgIndex */
        DTCStatusStPtr->ExtendDTCStatus  = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC;                   /* [GUD]EventStrgIndex */
        DTCStatusStPtr->ExtendDTCStatus2 = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2;                  /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_StatusOfDTC                           */
/* Description   | Set statusOfDTC.                                         */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] StatusOfDTC :                                      */
/*               |        statusOfDTC.                                      */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_DataMngC_SetER_ExtendDTCStatus. */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_StatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTCOld;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        statusOfDTCOld   =   Dem_EventRecordList[EventStrgIndex].StatusOfDTC;       /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].StatusOfDTC   =   StatusOfDTC;          /* [GUD]EventStrgIndex */

        if ( statusOfDTCOld != StatusOfDTC )
        {
            /* Change Dem_EventNvMStatus */
            recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
        }
    }

    return ;
}
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )  */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_DTCStatusSt                           */
/* Description   | set DTCStatus structure.                                 */
/* Preconditions |                                                          */
/*               | The fault record is updated(with updateconsistencyId)    */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] DTCStatusStPtr :                                    */
/* Return Value  | none                                                     */
/* Notes         | The caller calls this function after checking the record data difference.    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_SetEventRecord.       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_DTCStatusSt
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        Dem_EventRecordList[EventStrgIndex].StatusOfDTC                 = DTCStatusStPtr->DTCStatus;            /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC           = DTCStatusStPtr->ExtendDTCStatus;      /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2          = DTCStatusStPtr->ExtendDTCStatus2;     /* [GUD]EventStrgIndex */

        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
    }
    else
    {
        /* No process */
    }

    return;
}

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_DTCStatusSt_AtUpdateFaultRecord       */
/* Description   | Sets the data body and consistencyId of the event record */
/*               | to the event record list corresponding to the specified  */
/*               | event index. (for Dem_DataCtl subunit)                   */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/*               | The fault record is updated(with updateconsistencyId)    */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] EventRecordPtr :                                    */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/*               |                     &Dem_TmpEventMemoryEntry.EventRecord */
/*               |                     AUTOMATIC                            */
/*               | [in] ConsistencyId :                                     */
/*               |        ConsistencyId                                     */
/* Return Value  | none                                                     */
/* Notes         | The caller calls this function after checking the record data difference.    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord.   */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_DTCStatusSt_AtUpdateFaultRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        Dem_EventRecordList[EventStrgIndex].StatusOfDTC                 = DTCStatusStPtr->DTCStatus;            /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC           = DTCStatusStPtr->ExtendDTCStatus;      /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2          = DTCStatusStPtr->ExtendDTCStatus2;     /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault  = ConsistencyId;                        /* [GUD]EventStrgIndex */

        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );       /* [GUD]EventStrgIndex */
    }
    else
    {
        /* No process */
    }

    return;
}
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_ExtendDTCStatus                       */
/* Description   | Set extend statusOfDTC.                                  */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ExtendStatusOfDTC :                                 */
/*               |        extend status of DTC.                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_ExtendDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) ExtendStatusOfDTC
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) extendStatusOfDTCOld;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        extendStatusOfDTCOld   =   Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC;                   /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC   =   ExtendStatusOfDTC;                      /* [GUD]EventStrgIndex */

        if ( extendStatusOfDTCOld != ExtendStatusOfDTC )
        {
            /* Change Dem_EventNvMStatus */
            recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_ExtendDTCStatus2                      */
/* Description   | Set extend statusOfDTC.                                  */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ExtendStatusOfDTC2 :                                */
/*               |        extend status of DTC.                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_ExtendDTCStatus2
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) ExtendStatusOfDTC2
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2Old;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        extendStatusOfDTC2Old   =   Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2;                 /* [GUD]EventStrgIndex */
        Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2   =   ExtendStatusOfDTC2;                    /* [GUD]EventStrgIndex */

        if ( extendStatusOfDTC2Old != ExtendStatusOfDTC2 )
        {
            /* Change Dem_EventNvMStatus */
            recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
        }
    }

    return ;
}

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_FailureCounter                        */
/* Description   | Gets the failure counter of the event record list corre- */
/*               | sponding to the specified event index.                   */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] FailureCounterPtr :                                */
/*               |        The pointer of the failure counter.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_GetER_StatusOfDTC.    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_FailureCounter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *FailureCounterPtr = Dem_EventRecordList[EventStrgIndex].FailureCounter;                            /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_OccurrenceCounter                     */
/* Description   | Gets the occurrence counter of the event record list co- */
/*               | rresponding to the specified event index.                */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] OccurrenceCounterPtr :                             */
/*               |        The pointer of the occurrence counter.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DataMngC_GetER_StatusOfDTC.    */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_OccurrenceCounter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC, AUTOMATIC ) OccurrenceCounterPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *OccurrenceCounterPtr = Dem_EventRecordList[EventStrgIndex].OccurrenceCounter;                      /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetEventRecord                              */
/* Description   | Sets the data body of the event record to the event rec- */
/*               | ord list corresponding to the specified event index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] EventRecordPtr :                                    */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/*               |                     &Dem_TmpEventMemoryEntry.EventRecord */
/*               |                     AUTOMATIC                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_DataMng_SetEventCtlRecord( EventStrgIndex, EventRecordPtr );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord          */
/* Description   | Sets the data body and consistencyId of the event record */
/*               | to the event record list corresponding to the specified  */
/*               | event index. (for Dem_DataCtl subunit)                   */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/*               | The fault record is updated(with updateconsistencyId)    */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] EventRecordPtr :                                    */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/*               |                     &Dem_TmpEventMemoryEntry.EventRecord */
/*               |                     AUTOMATIC                            */
/*               | [in] ConsistencyId :                                     */
/*               |        ConsistencyId                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault = ConsistencyId;                     /* [GUD]EventStrgIndex */

        Dem_DataMng_SetEventCtlRecord( EventStrgIndex, EventRecordPtr );
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_CompareEventRecord                          */
/* Description   | Compare record data : Event record.                      */
/* Preconditions |                                                          */
/*               |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                    &Dem_TmpEventMemoryEntry.EventRecord  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : same.                                */
/*               |        DEM_IRT_NG : different                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_CompareEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                      /* [GUD:if]EventStrgIndex */
    {
        retVal = Dem_DataMng_CmpWithEventRecord( EventStrgIndex, EventRecordPtr );              /* [GUD]EventStrgIndex *//* [GUDCHK:CALLER]EventRecordPtr */
    }
    else
    {
        /* No process */
    }

    return retVal;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngM_GetEventRecord                              */
/* Description   | Gets the data body and consistency counters of the even- */
/*               | t record from the event record list corresponding to th- */
/*               | e specified event index.                                 */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMngM_GetEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_DataMng_GetEventRecord_Ctl( EventStrgIndex, EventRecordPtr );       /* [GUD]EventStrgIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_EventMng_GetPassedBitmapData( EventStrgIndex, EventRecordPtr );     /* [GUD]EventStrgIndex */
#endif /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )          */

        Dem_DataMng_GetEventRecord_MM( EventStrgIndex, EventRecordPtr );        /* [GUD]EventStrgIndex */
    }

    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_DataMngM_InitEventRecord                             */
/* Description   |                                                          */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngM_InitEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Checks the range of the specified index. */
    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_DataMng_InitEventRecord_Ctl( EventStrgIndex );

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_EventMng_SetPassedBitmapData( &Dem_EventRecordList[EventStrgIndex], DEM_EVENTCTRLBITMAP_ALL_OFF );   /* [GUD]EventStrgIndex */
#endif /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )          */

#if ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )    /* [FuncSw] */
        Dem_EventMng_InitRecord_Padding( &Dem_EventRecordList[EventStrgIndex] );                            /* [GUD]EventStrgIndex */
#endif /* ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )  */
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_InitEventCtlRecordData                      */
/* Description   | Initializes the specified event record.                  */
/* Preconditions |                                                          */
/* Parameters    | [out] EventRecordPtr :                                   */
/*               |                  &Dem_TmpDisabledRecord.EventRecord      */
/*               |                  &Dem_TmpEventMemoryEntry.EventRecord    */
/*               |                  AUTOMATIC                               */
/*               |        The specified event record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_InitEventCtlRecordData
(
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    /* Sets initial value to the specified event record. */

    /* The fault index. */
    EventRecordPtr->FaultIndex              = DEM_FAULTINDEX_INITIAL;

    /* The status of DTC. */
    EventRecordPtr->StatusOfDTC             = DEM_DTCSTATUS_BYTE_DEFAULT;

    /* The status of DTC. */
    EventRecordPtr->ExtendStatusOfDTC       = DEM_DTCSTATUSEX_BYTE_DEFAULT;
    EventRecordPtr->ExtendStatusOfDTC2      = DEM_DTCSTATUSEX2_BYTE_DEFAULT;

    /* The counter of fail event. */
    EventRecordPtr->FailureCounter          = DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )    /* [FuncSw]   */
    /* The counter of event occurrence. */
    EventRecordPtr->OccurrenceCounter       = DEM_EVENT_OCCURRENCE_COUNT_INITIAL_VALUE;
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )           */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_CopyEventCtlRecordData                      */
/* Description   | copy the specified event record.                         */
/* Preconditions |                                                          */
/* Parameters    | [out] DestEventRecordPtr :                               */
/*               | [in] SrcEventRecordPtr :                                 */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_CopyEventCtlRecordData
(
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, AUTOMATIC ) DestEventRecordPtr,
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
)
{
    /* Sets initial value to the specified event record. */

    /* The fault index. */
    DestEventRecordPtr->FaultIndex              = SrcEventRecordPtr->FaultIndex;

    /* The status of DTC. */
    DestEventRecordPtr->StatusOfDTC             = SrcEventRecordPtr->StatusOfDTC;

    /* The status of DTC. */
    DestEventRecordPtr->ExtendStatusOfDTC       = SrcEventRecordPtr->ExtendStatusOfDTC;
    DestEventRecordPtr->ExtendStatusOfDTC2      = SrcEventRecordPtr->ExtendStatusOfDTC2;

    /* The counter of fail event. */
    DestEventRecordPtr->FailureCounter          = SrcEventRecordPtr->FailureCounter;

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    /* The counter of event occurrence. */
    DestEventRecordPtr->OccurrenceCounter       = SrcEventRecordPtr->OccurrenceCounter;
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_SetEventRecordConsistencyId                  */
/* Description   | Sets the consistency Id of the event record              */
/*               | corresponding to the specified event index.              */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        ConsistencyId                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_SetEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Checks the range of the specified index. */
    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault = ConsistencyId;                     /* [GUD]EventStrgIndex */

        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventRecordConsistencyId                  */
/* Description   | Gets the consistency Id of the event record              */
/*               | corresponding to the specified event index.              */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        ConsistencyIdPtr                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Checks the range of the specified index. */
    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        *ConsistencyIdPtr = Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault;                 /* [GUD]EventStrgIndex */
    }

    return;
}


#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_UpdateEventRecordConsistencyId               */
/* Description   | Decrement and set consistencyId of Event record.         */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] ConsistencyIdPtr :                                 */
/*               |        ConsistencyIdPtr                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_UpdateEventRecordConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) ConsistencyIdPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    /* Checks the range of the specified index. */
    if( EventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]EventStrgIndex */
    {
        Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault = Dem_UtlCid_CalcConsistencyId( Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault );    /* [GUD]EventStrgIndex */
        *ConsistencyIdPtr = Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault;                 /* [GUD]EventStrgIndex */

        /* Change Dem_EventNvMStatus */
        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
    }

    return;
}
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */


/****************************************************************************/
/* Function Name | Dem_DataMng_InitEventRecord_Ctl                          */
/* Description   | Initializes the specified event record.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitEventRecord_Ctl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    /* Sets the initial values to the specified event records. */
    Dem_EventRecordList[EventStrgIndex].FaultIndex              = DEM_FAULTINDEX_INITIAL;                                   /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].StatusOfDTC             = DEM_DTCSTATUS_BYTE_DEFAULT;                               /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC       = DEM_DTCSTATUSEX_BYTE_DEFAULT;                             /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2      = DEM_DTCSTATUSEX2_BYTE_DEFAULT;                            /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].FailureCounter          = DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;                     /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_EventRecordList[EventStrgIndex].OccurrenceCounter       = DEM_EVENT_OCCURRENCE_COUNT_INITIAL_VALUE;                 /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */

    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
    {
        Dem_EventRecordList[EventStrgIndex].ClearID = Dem_ClrInfoMng_GetObdClearID();                                       /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else
    {
        Dem_EventRecordList[EventStrgIndex].ClearID = Dem_ClrInfoMng_GetClearID();                                          /* [GUDCHK:CALLER]EventStrgIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventCtlRecord                            */
/* Description   | Get event record. (Control data)                         */
/*               |                                                          */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                    &Dem_TmpDisabledRecord.EventRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.EventRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventCtlRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) DestEventRecordPtr
)
{
    DestEventRecordPtr->FaultIndex              = Dem_EventRecordList[EventStrgIndex].FaultIndex;                           /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->StatusOfDTC             = Dem_EventRecordList[EventStrgIndex].StatusOfDTC;                          /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->ExtendStatusOfDTC       = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC;                    /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->ExtendStatusOfDTC2      = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2;                   /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->FailureCounter          = Dem_EventRecordList[EventStrgIndex].FailureCounter;                       /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    DestEventRecordPtr->OccurrenceCounter       = Dem_EventRecordList[EventStrgIndex].OccurrenceCounter;                    /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_SetEventCtlRecord                            */
/* Description   | Set event record. (Control data)                         */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                     &Dem_TmpEventMemoryEntry.EventRecord */
/*               |                     AUTOMATIC                            */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_SetEventCtlRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    Dem_EventRecordList[EventStrgIndex].FaultIndex                  = SrcEventRecordPtr->FaultIndex;                        /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].StatusOfDTC                 = SrcEventRecordPtr->StatusOfDTC;                       /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC           = SrcEventRecordPtr->ExtendStatusOfDTC;                 /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2          = SrcEventRecordPtr->ExtendStatusOfDTC2;                /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].FailureCounter              = SrcEventRecordPtr->FailureCounter;                    /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_EventRecordList[EventStrgIndex].OccurrenceCounter           = SrcEventRecordPtr->OccurrenceCounter;                 /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
    if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
    {
        Dem_EventRecordList[EventStrgIndex].ClearID = Dem_ClrInfoMng_GetObdClearID();                                       /* [GUDCHK:CALLER]EventStrgIndex */
    }
    else
    {
        Dem_EventRecordList[EventStrgIndex].ClearID = Dem_ClrInfoMng_GetClearID();                                          /* [GUDCHK:CALLER]EventStrgIndex */
    }

    /* Change Dem_EventNvMStatus */
    recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );

    return ;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventRecord_Ctl                           */
/* Description   | Get event record data. (for Control data)                */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |         The pointer of the event record corresponding to */
/*               |         the specified event index.                       */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecord_Ctl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    P2VAR( Dem_EventRecordType, AUTOMATIC, AUTOMATIC ) DestEventRecordPtr
)
{
    DestEventRecordPtr->FaultIndex              = Dem_EventRecordList[EventStrgIndex].FaultIndex;                           /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->StatusOfDTC             = Dem_EventRecordList[EventStrgIndex].StatusOfDTC;                          /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->ExtendStatusOfDTC       = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC;                    /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->ExtendStatusOfDTC2      = Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2;                   /* [GUDCHK:CALLER]EventStrgIndex */
    DestEventRecordPtr->FailureCounter          = Dem_EventRecordList[EventStrgIndex].FailureCounter;                       /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    DestEventRecordPtr->OccurrenceCounter       = Dem_EventRecordList[EventStrgIndex].OccurrenceCounter;                    /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    DestEventRecordPtr->ClearID                 = Dem_EventRecordList[EventStrgIndex].ClearID;                              /* [GUDCHK:CALLER]EventStrgIndex */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventRecord_MM                            */
/* Description   | Get event record data. (for MM data)                     */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |         the specified event index.                       */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_GetEventRecord_MM
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                        /* [PRMCHK:CALLER] */
    P2VAR( Dem_EventRecordType, AUTOMATIC, AUTOMATIC ) DestEventRecordPtr
)
{
    DestEventRecordPtr->ConsistencyCounterForFault = Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault;        /* [GUDCHK:CALLER]EventStrgIndex */

    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_DataMng_CmpWithEventRecord                           */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] CheckEventRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                            /* [PRMCHK:CALLER] */
    P2CONST( Dem_EventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckEventRecordPtr    /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) eventRecordPtr;

    retVal = DEM_IRT_OK;

    eventRecordPtr  =   &Dem_EventRecordList[EventStrgIndex];                                   /* [GUDCHK:CALLER]EventStrgIndex *//* [GUD:CFG:IF_GUARDED: EventStrgIndex ]eventRecordPtr */

    if( eventRecordPtr->StatusOfDTC != CheckEventRecordPtr->StatusOfDTC )                       /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( eventRecordPtr->FailureCounter != CheckEventRecordPtr->FailureCounter )            /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    else if( eventRecordPtr->OccurrenceCounter != CheckEventRecordPtr->OccurrenceCounter )      /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    else if( eventRecordPtr->FaultIndex != CheckEventRecordPtr->FaultIndex )                    /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( eventRecordPtr->ExtendStatusOfDTC != CheckEventRecordPtr->ExtendStatusOfDTC )      /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else if( eventRecordPtr->ExtendStatusOfDTC2 != CheckEventRecordPtr->ExtendStatusOfDTC2 )    /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]CheckEventRecordPtr */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_GetFactoryCheckResultOfEventRecord           */
/* Description   | get factory check result of event record.                */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | boolean                                                  */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMng_GetFactoryCheckResultOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;

    resultOfFactoryCheck = (boolean)FALSE;

    if( Dem_EventRecordList[EventStrgIndex].StatusOfDTC == (Dem_UdsStatusByteType)DEM_DATA_INITIAL_VALUE )                  /* [GUDCHK:CALLER]EventStrgIndex */
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }

    return  resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_CheckClearIDOfEventRecord                    */
/* Description   | get clearId check result of event record.                */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] ClearID                                             */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMng_CheckClearIDOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;

    resultOfClearIdCheck = (boolean)FALSE;

    if( Dem_EventRecordList[EventStrgIndex].ClearID == ClearID )                                                            /* [GUDCHK:CALLER]EventStrgIndex */
    {
        resultOfClearIdCheck = (boolean)TRUE;
    }

    return  resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_CheckConsistencyIdOfEventRecord              */
/* Description   | get ConsistencyId check result of event record.          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ConsistencyId check OK              */
/*               |          FALSE     : ConsistencyId check NG              */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataMng_CheckConsistencyIdOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( boolean, AUTOMATIC ) resultOfConsistencyIdCheck;

    resultOfConsistencyIdCheck = (boolean)FALSE;

    if( Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault == ConsistencyId )                                   /* [GUDCHK:CALLER]EventStrgIndex */
    {
        resultOfConsistencyIdCheck = (boolean)TRUE;
    }

    return  resultOfConsistencyIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitER_FaultIndex                            */
/* Description   | Initializes the fault index of specified event record.   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_InitER_FaultIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    Dem_EventRecordList[EventStrgIndex].FaultIndex = DEM_FAULTINDEX_INITIAL;                                                /* [GUDCHK:CALLER]EventStrgIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_InitSavedZoneOfEventRecord                   */
/* Description   | Initialize savedzone of Event record                     */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_InitSavedZoneOfEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex         /* [PRMCHK:CALLER] */
)
{
    Dem_EventRecordList[EventStrgIndex].FaultIndex                  = DEM_FAULTINDEX_INITIAL;                               /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].StatusOfDTC                 = DEM_DTCSTATUS_FACTORY_DEFAULT;                        /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].FailureCounter              = DEM_FAILURECYCLE_COUNT_FACTORY_DEFAULT;               /* [GUDCHK:CALLER]EventStrgIndex */
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_EventRecordList[EventStrgIndex].OccurrenceCounter           = DEM_EVENT_OCCURRENCE_COUNT_FACTORY_DEFAULT;           /* [GUDCHK:CALLER]EventStrgIndex */
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    Dem_EventRecordList[EventStrgIndex].ConsistencyCounterForFault  = DEM_CONSISTENCY_INITIAL;                              /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ClearID                     = DEM_CLRINFO_RECORD_INITIAL;                           /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC           = DEM_DTCSTATUSEX_FACTORY_DEFAULT;                      /* [GUDCHK:CALLER]EventStrgIndex */
    Dem_EventRecordList[EventStrgIndex].ExtendStatusOfDTC2          = DEM_DTCSTATUSEX2_FACTORY_DEFAULT;                     /* [GUDCHK:CALLER]EventStrgIndex */

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_EventMng_SetPassedBitmapData( &Dem_EventRecordList[EventStrgIndex], DEM_PASSEDBITMAP_FACTORY_DEFAULT );   /* [GUDCHK:CALLER]EventStrgIndex */
#endif /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )          */

    return;
}


/****************************************************************************/
/* Function Name | Dem_EventMng_Init                                        */
/* Description   | Init process of Event.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )              /* [GUD:for]eventStrgIndex */
    {
        Dem_EventNvMStatus[ eventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;                                          /* [GUD]eventStrgIndex */
    }
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_EventMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
    Dem_DataMng_Init();
    return;
}

/****************************************************************************/
/* Function Name | Dem_EventMng_InitSavedZone                               */
/* Description   | Initialize savedzone process of Event.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    recMngCmnKindEvent = Dem_RecMngCmnKindEvent;

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )              /* [GUD:for]eventStrgIndex */
    {
        Dem_DataMng_InitSavedZoneOfEventRecord( eventStrgIndex );                                                           /* [GUD]eventStrgIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )eventStrgIndex );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_EventMng_DataVerify                                  */
/* Description   | Verifies Event data.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_DataMng_DataVerify();

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventMng_SetRecordMirror                             */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_DataMngM_GetEventRecord( (Dem_u16_EventStrgIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpEventMirror );

    BlockMirrorPtr->MirrorPtr = &Dem_TmpEventMirror;

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_EventMng_ClearAllNotVerifiedRecord                   */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    loopCount = (Dem_u32_TotalRecordNumType)0U;
    retVal = DEM_IRT_OK;

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)( *ClearRecordIndexPtr ); eventStrgIndex < eventStorageNum; eventStrgIndex++ )    /* [GUD:for]eventStrgIndex */
    {
        if( loopCount < *RestOfProcessableNumPtr )
        {
            if( Dem_EventNvMStatus[ eventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                /* [GUD]eventStrgIndex */
            {
                Dem_DataMngM_InitEventRecord( eventStrgIndex );                                             /* [GUD]eventStrgIndex */
                Dem_EventNvMStatus[ eventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                    /* [GUD]eventStrgIndex */
            }
            loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
        }
        else
        {
            *ClearRecordIndexPtr = (Dem_u16_EventStrgIndexType)eventStrgIndex;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    if( eventStrgIndex >= eventStorageNum )
    {
        *RestOfProcessableNumPtr = (*RestOfProcessableNumPtr) - loopCount;  /* no wrap around */
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventMng_InitMirrorMemory                            */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventMng_InitMirrorMemory
( void )
{
    /* Sets the initial values to the specified event records. */
    Dem_TmpEventMirror.FaultIndex                   = DEM_FAULTINDEX_INITIAL;
    Dem_TmpEventMirror.StatusOfDTC                  = DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_TmpEventMirror.ExtendStatusOfDTC            = DEM_DTCSTATUSEX_BYTE_DEFAULT;
    Dem_TmpEventMirror.ExtendStatusOfDTC2           = DEM_DTCSTATUSEX2_BYTE_DEFAULT;
    Dem_TmpEventMirror.FailureCounter               = DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_TmpEventMirror.OccurrenceCounter            = DEM_EVENT_OCCURRENCE_COUNT_INITIAL_VALUE;
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    Dem_TmpEventMirror.ConsistencyCounterForFault   = DEM_CONSISTENCY_INITIAL;

    /* Stores unused values to initialize the structure before reading */
    Dem_TmpEventMirror.ClearID                      = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_EventMng_SetPassedBitmapData( &Dem_TmpEventMirror, DEM_EVENTCTRLBITMAP_ALL_OFF );
#endif /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )          */

#if ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )    /* [FuncSw] */
    Dem_EventMng_InitRecord_Padding( &Dem_TmpEventMirror );
#endif /* ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )  */

    return;
}
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )     */

#if ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventMng_InitRecord_Padding                          */
/* Description   | Initializes EventRecord padding area.                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] EventRecordPtr :                                   */
/*               |        The specified event record to initialize.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_FaultMng_InitFRData_Padding. */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_EventMng_InitRecord_Padding
(
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) EventRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) idx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) eventRecordBlockPaddingSize;

    eventRecordBlockPaddingSize = Dem_EventRecordBlockPaddingSize;
    for ( idx = (Dem_u16_PaddingIndexType)0U; idx < eventRecordBlockPaddingSize; idx++ )            /* [GUD:for]idx */
    {
        EventRecordPtr->Reserve[idx] = DEM_DATA_RESERVE_INITIAL_VALUE;                              /* [GUD]idx *//* [ARYCHK] DEM_EVENT_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / idx */
    }

    return ;
}
#endif  /* ( DEM_EVENT_RECORD_PADDING_EXIST == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventMng_GetEventIdFromRecordData                    */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EventMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex  =   ( Dem_u16_EventStrgIndexType )RecordIndex;

    retVal  =   Dem_DataMng_GetEventIdFromEventStrgIndex( eventStrgIndex, EventIdPtr );

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
