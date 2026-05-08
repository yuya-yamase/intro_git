/* Dem_UdmEventMng_c(v5-7-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmEventMng/CODE                                      */
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
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmEventRecordTable.h"
#include "Dem_UdmMng_local.h"
#include "Dem_UdmMng_GetRecordData.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

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

static FUNC( void, DEM_CODE ) Dem_UdmEventMngC_GetCtlRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) DestEventRecordPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_CmpWithEventRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckEventRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetEventCtlRecord
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
);


static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmEventRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitMirrorMemory
( void );
#if ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord_Padding
(
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmEventRecordPtr
);
#endif /*   ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )  */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_UdmEventRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdmEventMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static VAR( Dem_UdmEventMemoryRecordType, DEM_VAR_NO_INIT ) Dem_UdmEventMemoryRecordList[DEM_USER_DEFINED_MEMORY_NUM];


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_InitEvtMemRecData                       */
/* Description   | Initializes the specified record of event memory record  */
/*               | list.                                                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitEvtMemRecData
(
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    /* Sets initial values to the specified event memory record. */
    EventMemoryRecordPtr->NumberOfFreezeFrameRecords    = DEM_NUMOFFFREC_INITIAL;
    EventMemoryRecordPtr->NumberOfEventMemoryEntries    = DEM_NUMOFEVTMEMENT_INITIAL;
    EventMemoryRecordPtr->LastOfFaultOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INITIAL;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_InitAllEvtMemRecData                    */
/* Description   | Initializes the specified record of event memory record  */
/*               | list.                                                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitAllEvtMemRecData
( void )
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    for( udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)0U ; udmGroupKindIndex < userDefinedMemoryNum ; udmGroupKindIndex++ )  /* [GUD:for]udmGroupKindIndex */
    {
        /* Sets initial values to the specified event memory record. */
        Dem_UdmEventMemoryRecordList[udmGroupKindIndex].NumberOfFreezeFrameRecords    = DEM_NUMOFFFREC_INITIAL;                     /* [GUD]udmGroupKindIndex */
        Dem_UdmEventMemoryRecordList[udmGroupKindIndex].NumberOfEventMemoryEntries    = DEM_NUMOFEVTMEMENT_INITIAL;                 /* [GUD]udmGroupKindIndex */
        Dem_UdmEventMemoryRecordList[udmGroupKindIndex].LastOfFaultOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INITIAL;            /* [GUD]udmGroupKindIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_SetAllNumberOfEventMemoryRecord         */
/* Description   | Initializes the specified record of event memory record  */
/*               | list.                                                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetAllNumberOfEventMemoryRecord
( void )
{
    Dem_UdmFaultMng_GetNumOfStoredFault( &(Dem_UdmEventMemoryRecordList[0]) );
    Dem_UdmFFDMng_GetNumOfStoredUdmFFD( &(Dem_UdmEventMemoryRecordList[0]) );

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_InitRecord                              */
/* Description   | Initializes the specified event record.                  */
/* Preconditions |                                                          */
/* Parameters    | [out] EventRecordPtr :                                   */
/*               |                  &Dem_TmpDisabledRecord.EventRecord      */
/*               |                  &Dem_TmpEventMemoryEntry.EventRecord    */
/*               |                  AUTOMATIC                               */
/*               |        The specified event record to initialize.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_InitRecord
(
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    /* Sets initial value to the specified event record. */

    /* The fault index. */
    EventRecordPtr->UdmFaultIndex              = DEM_UDMFAULTINDEX_INITIAL;

    /* The status of DTC. */
    EventRecordPtr->StatusOfDTC             = DEM_DTCSTATUS_BYTE_DEFAULT;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_GetRecord                               */
/* Description   | Gets the data body of the event record from the event r- */
/*               | ecord list corresponding to the specified event index. - */
/*               | (for Dem_DataCtl subunit)                                */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventIndex :                                        */
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
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmEventRecordPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );
            Dem_UdmEventMngC_GetCtlRecord( udmGroupKindIndex, udmEventStrgIndex, UdmEventRecordPtr );
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_GetCtlRecord                            */
/* Description   | Get event record. (Control data)                         */
/*               |                                                          */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                    &Dem_TmpDisabledRecord.EventRecord    */
/*               |                    &Dem_TmpEventMemoryEntry.EventRecord  */
/*               |                    AUTOMATIC                             */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmEventMngC_GetCtlRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) DestEventRecordPtr
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;

    udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex ); /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */

    if ( udmEventRecordPtr != NULL_PTR )                /* [GUD:if]udmEventRecordPtr */
    {
        udmFaultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( UdmGroupKindIndex );    /* [GUD]UdmGroupKindIndex */

        if( udmEventRecordPtr->UdmFaultIndex < udmFaultRecordNum )                      /* [GUD]udmEventRecordPtr */
        {
            DestEventRecordPtr->UdmFaultIndex = udmEventRecordPtr->UdmFaultIndex;       /* [GUD]udmEventRecordPtr */
        }
        else
        {
            DestEventRecordPtr->UdmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
        }

        DestEventRecordPtr->StatusOfDTC = udmEventRecordPtr->StatusOfDTC;               /* [GUD]udmEventRecordPtr */
    }
    else
    {
        DestEventRecordPtr->UdmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
        DestEventRecordPtr->StatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_GetEventMemoryRecord                    */
/* Description   | Gets the EventMemory record from the EventMemory record- */
/*               |  list                                                    */
/*               |  (for Dem_DataCtl subunit)                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryGroupTable[].  */
/*               | [out] EventMemoryRecordPtr :                             */
/*               |        The pointer of the EventMemory record             */
/*               |         &Dem_TmpEventMemoryEntry.EventMemoryRecordList   */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_GetEventMemoryRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]UdmGroupKindIndex */
    {
        EventMemoryRecordPtr->NumberOfFreezeFrameRecords    = Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].NumberOfFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex */
        EventMemoryRecordPtr->NumberOfEventMemoryEntries    = Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].NumberOfEventMemoryEntries;   /* [GUD]UdmGroupKindIndex */
        EventMemoryRecordPtr->LastOfFaultOccurrenceOrder    = Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].LastOfFaultOccurrenceOrder;   /* [GUD]UdmGroupKindIndex */
    }
    else
    {
        EventMemoryRecordPtr->NumberOfFreezeFrameRecords    = DEM_NUMOFFFREC_INITIAL;
        EventMemoryRecordPtr->NumberOfEventMemoryEntries    = DEM_NUMOFEVTMEMENT_INITIAL;
        EventMemoryRecordPtr->LastOfFaultOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INITIAL;
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_SetEventMemoryRecord                    */
/* Description   | Sets the EventMemory record to the EventMemory record l- */
/*               | ist (for Dem_DataCtl subunit)                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryGroupTable[].  */
/*               | [in] EventMemoryRecordPtr :                              */
/*               |        The pointer of the EventMemory record             */
/*               |         &Dem_TmpEventMemoryEntry.EventMemoryRecordList   */
/*               |         AUTOMATIC                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetEventMemoryRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2CONST( Dem_UdmEventMemoryRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventMemoryRecordPtr
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]UdmGroupKindIndex */
    {
        Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].NumberOfFreezeFrameRecords    = EventMemoryRecordPtr->NumberOfFreezeFrameRecords;   /* [GUD]UdmGroupKindIndex */
        Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].NumberOfEventMemoryEntries    = EventMemoryRecordPtr->NumberOfEventMemoryEntries;   /* [GUD]UdmGroupKindIndex */
        Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].LastOfFaultOccurrenceOrder    = EventMemoryRecordPtr->LastOfFaultOccurrenceOrder;   /* [GUD]UdmGroupKindIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_ResetLastOfFaultOccurrenceOrder         */
/* Description   | Sets the EventMemory record to the EventMemory record l- */
/*               | ist (for Dem_DataCtl subunit)                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryGroupTable[].  */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_ResetLastOfFaultOccurrenceOrder
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]UdmGroupKindIndex */
    {
        Dem_UdmEventMemoryRecordList[UdmGroupKindIndex].LastOfFaultOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INITIAL;        /* [GUD]UdmGroupKindIndex */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_CompareEventRecord                      */
/* Description   | Compare record data : Event record.                      */
/* Preconditions |                                                          */
/*               |                                                          */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                    &Dem_TmpEventMemoryEntry.EventRecord  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : same.                                */
/*               |        DEM_IRT_NG : different                            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_CompareEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )
    {
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );
            retVal = Dem_UdmEventMngC_CmpWithEventRecord( udmGroupKindIndex, udmEventStrgIndex, EventRecordPtr );
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_CmpWithEventRecord                      */
/* Description   | compare data.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] CheckEventRecordPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : same.                               */
/*               |        DEM_IRT_NG  : different.                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_CmpWithEventRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckEventRecordPtr
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;

    udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex );    /* [GUD:RET:Not NULL_PTR] udmEventRecordPtr */

    if ( udmEventRecordPtr != NULL_PTR )        /* [GUD:if]udmEventRecordPtr */
    {
        if( udmEventRecordPtr->StatusOfDTC != CheckEventRecordPtr->StatusOfDTC )            /* [GUD]udmEventRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
        else if( udmEventRecordPtr->UdmFaultIndex != CheckEventRecordPtr->UdmFaultIndex )   /* [GUD]udmEventRecordPtr */
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            /* No Process */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_SetEventRecord                          */
/* Description   | Sets the data body of the event record to the event rec- */
/*               | ord list corresponding to the specified event index. (f- */
/*               | or Dem_DataCtl subunit)                                  */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] EventIndex :                                        */
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
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_SetEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

        if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );
            Dem_UdmEventMngC_SetEventCtlRecord( udmInfoTableIndex, udmGroupKindIndex, udmEventStrgIndex, EventRecordPtr );
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_SetEventCtlRecord                       */
/* Description   | Set event record. (Control data)                         */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [out] EventRecordPtr :                                   */
/*               |        The pointer of the event record corresponding to  */
/*               |        the specified event index.                        */
/*               |                     &Dem_TmpEventMemoryEntry.EventRecord */
/*               |                     AUTOMATIC                            */
/* Return Value  | none.                                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetEventCtlRecord
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2CONST( Dem_UdmEventRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) SrcEventRecordPtr
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;

    udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex );          /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */

    if ( udmEventRecordPtr != NULL_PTR )                                                        /* [GUD:if]udmEventRecordPtr */
    {
        udmEventRecordPtr->UdmFaultIndex = SrcEventRecordPtr->UdmFaultIndex;                    /* [GUD]udmEventRecordPtr */
        udmEventRecordPtr->StatusOfDTC = SrcEventRecordPtr->StatusOfDTC;                        /* [GUD]udmEventRecordPtr */

        udmEventRecordPtr->UdmClearID = Dem_ClrInfoMng_GetUdmClearID( UdmInfoTableIndex );      /* [GUD]udmEventRecordPtr */

        /* Change Dem_EventNvMStatus */
        recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ UdmGroupKindIndex ].DemRecMngCmnKindUdmEvent;                /* [GUD]UdmGroupKindIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )UdmEventStrgIndex );     /* [GUD]UdmGroupKindIndex */
    }

    return ;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmEventMng_GetRecord                                */
/* Description   | Gets the data body and consistency counters of the udm - */
/*               | event record from the udme event record list correspond- */
/*               | ing to the specified udm event index.                    */
/* Preconditions | The specified udm event index be within the range of the */
/*               |  udm event record list.                                  */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The udm event index corresponding to the specific */
/*               |         udm event record.                                */
/*               | [out] UdmEventRecordPtr :                                */
/*               |        The pointer of the udm event record corresponding */
/*               |         to the specified udm event index.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_GetRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex,
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) DestUdmEventRecordPtr
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */
    if ( udmEventRecordPtr != NULL_PTR )                                                /* [GUD:if]udmEventRecordPtr */
    {
        /* Dem_UdmEventMng_GetRecord_Ctl */
        udmFaultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( UdmGroupKindIndex );    /* [GUD]UdmGroupKindIndex */

        if( udmEventRecordPtr->UdmFaultIndex < udmFaultRecordNum )                      /* [GUD]udmEventRecordPtr */
        {
            DestUdmEventRecordPtr->UdmFaultIndex = udmEventRecordPtr->UdmFaultIndex;    /* [GUD]udmEventRecordPtr */
        }
        else
        {
            DestUdmEventRecordPtr->UdmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
        }
        DestUdmEventRecordPtr->StatusOfDTC             = udmEventRecordPtr->StatusOfDTC;    /* [GUD]udmEventRecordPtr */
        DestUdmEventRecordPtr->UdmClearID              = udmEventRecordPtr->UdmClearID;     /* [GUD]udmEventRecordPtr */

        /* Dem_UdmEventMng_GetRecord_MM */
        DestUdmEventRecordPtr->ConsistencyIdForFault = udmEventRecordPtr->ConsistencyIdForFault;    /* [GUD]udmEventRecordPtr */

        retVal = DEM_IRT_OK;
    }
    else
    {
        DestUdmEventRecordPtr->UdmFaultIndex            = DEM_UDMFAULTINDEX_INITIAL;
        DestUdmEventRecordPtr->StatusOfDTC              = DEM_DTCSTATUS_BYTE_DEFAULT;
        DestUdmEventRecordPtr->UdmClearID               = DEM_CLRINFO_RECORD_INITIAL;
        DestUdmEventRecordPtr->ConsistencyIdForFault    = DEM_CONSISTENCY_INITIAL;
    }
    return retVal;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_DataMng_SetEventRecordConsistencyId                  */
/* Description   | Sets the consistency Id of the udm event record          */
/*               | corresponding to the specified udm event index.          */
/* Preconditions | none                                                     */
/*               |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        ConsistencyId                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMng_SetEventRecordConsistencyId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* Checks the range of the specified index. */
    if( UdmEventIndex < udmEventConfigureNum )                                      /* [GUD:if]UdmEventIndex */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );                                               /* [GUD]UdmEventIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );  /* [GUD]UdmEventIndex */

        if( udmGroupKindIndex < userDefinedMemoryNum )                                                                  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex ); /* [GUD]UdmGroupKindIndex */
            udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex );              /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */

            if ( udmEventRecordPtr != NULL_PTR )                                /* [GUD:if]udmEventRecordPtr */
            {
                udmEventRecordPtr->ConsistencyIdForFault = ConsistencyId;       /* [GUD]udmEventRecordPtr */
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMng_InitRecord                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The udm event index corresponding to the specific */
/*               |         udm event record.                                */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
)
{
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        udmEventRecordNum = Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum;   /* [GUD]UdmGroupKindIndex */
        if( UdmEventStrgIndex < udmEventRecordNum )                                         /* [GUD:if]UdmEventStrgIndex */
        {
            Dem_UdmEventMng_InitRecord_Ctl( UdmGroupKindIndex, UdmEventStrgIndex );         /* [GUD]UdmGroupKindIndex *//* [GUD]UdmEventStrgIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMng_InitRecord_Ctl                           */
/* Description   | Initializes the specified udm event record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventStrgIndex :                                 */
/*               |        The udm event index corresponding to the specific */
/*               |         udm event record.                                */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord_Ctl
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, UdmEventStrgIndex );  /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */
    if ( udmEventRecordPtr != NULL_PTR )                                                            /* [GUD:if]udmEventRecordPtr */
    {
        udmInfoTableIndex = Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex( UdmGroupKindIndex );  /* [GUD]UdmGroupKindIndex */

        /* Sets the initial values to the specified event records. */
        udmEventRecordPtr->UdmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;                               /* [GUD]udmEventRecordPtr */
        udmEventRecordPtr->StatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;                                /* [GUD]udmEventRecordPtr */

        udmEventRecordPtr->UdmClearID = Dem_ClrInfoMng_GetUdmClearID( udmInfoTableIndex );          /* [GUD]udmEventRecordPtr */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMng_Init                                     */
/* Description   | Init process of UDM Event.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventRecordNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )
    {
        udmEventRecordNum = Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum;   /* [GUD]udmGroupKindIndex */
        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)0U; udmEventStrgIndex < udmEventRecordNum; udmEventStrgIndex++ )
        {
            Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemUdmEventNvMStatusPtr[ udmEventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;   /* [GUD]udmGroupKindIndex */    /* [GUD]udmEventStrgIndex *//* [ARYCHK] Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum / 1 / udmEventStrgIndex */
        }
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_UdmEventMng_InitMirrorMemory();
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */
    Dem_UdmMngVld_DataInit();

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMng_InitSavedZone                            */
/* Description   | Initialize savedzone process of ClrInfo.                 */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventRecordNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex    = ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )
    {
        udmEventRecordNum = Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum;   /* [GUD]udmGroupKindIndex */
        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)0U; udmEventStrgIndex < udmEventRecordNum; udmEventStrgIndex++ )
        {
            udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex );  /* [GUD]udmGroupKindIndex *//* [GUD]udmEventStrgIndex *//* [GUD:RET:IF_GUARDED udmGroupKindIndex/udmEventStrgIndex] udmEventRecordPtr */

            udmEventRecordPtr->UdmFaultIndex           = DEM_UDMFAULTINDEX_INITIAL;                         /* [GUD]udmEventRecordPtr */
            udmEventRecordPtr->StatusOfDTC             = DEM_DTCSTATUS_FACTORY_DEFAULT;                     /* [GUD]udmEventRecordPtr */
            udmEventRecordPtr->ConsistencyIdForFault   = DEM_CONSISTENCY_INITIAL;                           /* [GUD]udmEventRecordPtr */
            udmEventRecordPtr->UdmClearID              = DEM_CLRINFO_RECORD_INITIAL;                        /* [GUD]udmEventRecordPtr */

            recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemRecMngCmnKindUdmEvent;    /* [GUD]udmGroupKindIndex */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )udmEventStrgIndex );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMng_DataVerify                               */
/* Description   | Verifies Udm Event data.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_UdmMngVld_DataVerify( (Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex );

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmEventMng_SetRecordMirror                          */
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
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    (void)Dem_UdmEventMng_GetRecord( (Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex, (Dem_u16_UdmEventStrgIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpUdmEventMirror );  /* no return check required */

    BlockMirrorPtr->MirrorPtr = &Dem_TmpUdmEventMirror;

    return;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_UdmEventMng_ClearAllNotVerifiedRecord                */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_ClearAllNotVerifiedRecord
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventRecordNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;

    retVal = DEM_IRT_OK;
    loopCount = (Dem_u32_TotalRecordNumType)0U;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    udmGroupKindIndex = ( Dem_u16_UdmDemMemKindIndexType)RecordFieldIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]udmGroupKindIndex */
    {
        udmEventRecordNum = Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum;   /* [GUD]udmGroupKindIndex */
        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)( *ClearRecordIndexPtr ); udmEventStrgIndex < udmEventRecordNum; udmEventStrgIndex++ )  /* [GUD:for]udmEventStrgIndex */
        {
            if( loopCount < *RestOfProcessableNumPtr )
            {
                if( Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemUdmEventNvMStatusPtr[ udmEventStrgIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED ) /* [GUD]udmGroupKindIndex *//* [GUD]udmEventStrgIndex *//* [ARYCHK] udmEventRecordNum / 1 / udmEventStrgIndex *//* [ARYDESC] The registered data size of Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemUdmEventNvMStatusPtr is the same as Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum */
                {
                    Dem_UdmEventMng_InitRecord( udmGroupKindIndex, udmEventStrgIndex );
                    Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemUdmEventNvMStatusPtr[ udmEventStrgIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;     /* [GUD]udmGroupKindIndex *//* [GUD]udmEventStrgIndex *//* [ARYCHK] udmEventRecordNum / 1 / udmEventStrgIndex *//* [ARYDESC] The registered data size of Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemUdmEventNvMStatusPtr is the same as Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum */
                }
                loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
            }
            else
            {
                *ClearRecordIndexPtr = (Dem_u16_UdmEventStrgIndexType)udmEventStrgIndex;
                retVal = DEM_IRT_PENDING;
                break;
            }
        }

        if( udmEventStrgIndex >= udmEventRecordNum )
        {
            *RestOfProcessableNumPtr = (*RestOfProcessableNumPtr) - loopCount;  /* no wrap around */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_GetER_StatusOfDTC                       */
/* Description   | Gets the status of DTC of the event record list corresp- */
/*               | onding to the specified udm event index.                 */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific Ud- */
/*               |        m event record.                                   */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        The pointer of the status of DTC.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetER_StatusOfDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )                                             /* [GUD:if]UdmEventIndex */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );       /* [GUD]UdmEventIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );      /* [GUD]UdmEventIndex */

        if( udmGroupKindIndex < userDefinedMemoryNum )                                  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );
            udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex );    /* [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex/udmEventRecordPtr */

            if ( udmEventRecordPtr != NULL_PTR )                        /* [GUD:if]udmEventRecordPtr */
            {
                *StatusOfDTCPtr = udmEventRecordPtr->StatusOfDTC;       /* [GUD]udmEventRecordPtr */
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_SetER_StatusOfDTC                       */
/* Description   | Gets the status of DTC of the event record list corresp- */
/*               | onding to the specified udm event index.                 */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific Ud- */
/*               |        m event record.                                   */
/*               | [in] StatusOfDTC :                                       */
/*               |        status of DTC.                                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmEventMngC_SetER_StatusOfDTC
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldStatusOfDTC;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindUdmEvent;

    eventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < eventConfigureNum )                                         /* [GUD:if]UdmEventIndex */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );   /* [GUD]UdmEventIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );  /* [GUD]UdmEventIndex */

        if( udmGroupKindIndex < userDefinedMemoryNum )                  /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );     /* [GUD]udmGroupKindIndex *//* [GUD]UdmEventIndex */
            udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex );                  /* [GUD:RET:Not NULL_PTR] udmGroupKindIndex/udmEventStrgIndex/udmEventRecordPtr */

            if ( udmEventRecordPtr != NULL_PTR )                        /* [GUD:if]udmEventRecordPtr */
            {
                oldStatusOfDTC = udmEventRecordPtr->StatusOfDTC;        /* [GUD]udmEventRecordPtr */
                if ( oldStatusOfDTC != StatusOfDTC )
                {
                    udmEventRecordPtr->StatusOfDTC = StatusOfDTC;       /* [GUD]udmEventRecordPtr */

                    /* Change Dem_EventNvMStatus */
                    recMngCmnKindUdmEvent = Dem_UdmEventNvMStatus[ udmGroupKindIndex ].DemRecMngCmnKindUdmEvent;                /* [GUD]udmGroupKindIndex */
                    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindUdmEvent, ( Dem_u16_RecordIndexType )udmEventStrgIndex );     /* [GUD]udmEventStrgIndex */
                }
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmEventMngC_GetER_FaultIndex                        */
/* Description   | Gets the fault index of the event record list correspon- */
/*               | ding to the specified event index.                       */
/* Preconditions | The specified event index be within the range of the ev- */
/*               | ent record list.                                         */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The udm event index corresponding to the specifi- */
/*               |        c event record.                                   */
/*               | [out] FaultIndexPtr :                                    */
/*               |        The pointer of the fault index.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMngC_GetER_FaultIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
)
{
    P2CONST( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;

    retVal = DEM_IRT_NG;
    udmEventConfigureNum = Dem_UdmEventConfigureNum;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    if( UdmEventIndex < udmEventConfigureNum )                                      /* [GUD:if]UdmEventIndex */
    {
        /* Get udm group index. */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );   /* [GUD]UdmEventIndex */
        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );  /* [GUD]UdmEventIndex */

        if( udmGroupKindIndex < userDefinedMemoryNum )                                      /* [GUD:if]udmGroupKindIndex */
        {
            udmEventStrgIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex( udmGroupKindIndex, UdmEventIndex );         /* [GUD]udmGroupKindIndex *//* [GUD]UdmEventIndex */
            udmEventRecordPtr = ( P2CONST( Dem_UdmEventRecordType, TYPEDEF, DEM_VAR_SAVED_ZONE ) )Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex ); /* [GUD:RET:Not NULL_PTR] udmGroupKindIndex/udmEventStrgIndex/udmEventRecordPtr */
            if ( udmEventRecordPtr != NULL_PTR )                                            /* [GUD:if]udmEventRecordPtr */
            {
                udmFaultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( udmGroupKindIndex );

                if( udmEventRecordPtr->UdmFaultIndex < udmFaultRecordNum )                  /* [GUD]udmEventRecordPtr */
                {
                    *FaultIndexPtr = udmEventRecordPtr->UdmFaultIndex;                      /* [GUD]udmEventRecordPtr */
                }
                else
                {
                    *FaultIndexPtr = DEM_UDMFAULTINDEX_INITIAL;
                }
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmEventMng_InitMirrorMemory                         */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitMirrorMemory
( void )
{
    /* Sets the initial values to the specified event records. */
    Dem_TmpUdmEventMirror.UdmFaultIndex             = DEM_UDMFAULTINDEX_INITIAL;
    Dem_TmpUdmEventMirror.StatusOfDTC               = DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_TmpUdmEventMirror.ConsistencyIdForFault     = DEM_CONSISTENCY_INITIAL;

    /* Stores unused values to initialize the structure before reading */
    Dem_TmpUdmEventMirror.UdmClearID                = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )     /* [FuncSw] */
    Dem_UdmEventMng_InitRecord_Padding( &Dem_TmpUdmEventMirror );
#endif /*   ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )  */

    return;
}

#if ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmEventMng_InitRecord_Padding                       */
/* Description   | Initializes UdmEventRecord padding area.                 */
/* Preconditions |                                                          */
/* Parameters    | [out] UdmEventRecordPtr :                                */
/*               |        The specified udm event record to initialize.     */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmEventMng_InitRecord_Padding
(
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmEventRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) idx;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) udmEventRecordBlockPaddingSize;

    udmEventRecordBlockPaddingSize = Dem_UdmEventRecordBlockPaddingSize;

    /* initialize padding area */
    for ( idx = (Dem_u16_PaddingIndexType)0U; idx < udmEventRecordBlockPaddingSize; idx++ ) /* [GUD:for]idx */
    {
        UdmEventRecordPtr->Reserve[idx] = DEM_DATA_RESERVE_INITIAL_VALUE;                   /* [GUD]idx      *//* [ARYCHK] DEM_UDMEVENT_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / idx */
    }

    return;
}
#endif /*   ( DEM_UDMEVENT_RECORD_PADDING_EXIST == STD_ON )  */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_UdmEventMng_GetEventRecordPtr                        */
/* Description   | Calculates the pointer of the list of UdmEvent Record b- */
/*               | y the specified UdmGroupKindIndex and UdmEventIndex.     */
/* Preconditions | The specified UdmGroupKindIndex shall be within the range of */
/*               | the Dem_UserDefinedMemoryTable[].                        */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the specific Ev- */
/*               |        ent record.                                       */
/* Return Value  | Dem_UdmEventRecordType*                                  */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR] ReturnValue                       */
/* VariableGuard | [GUD:RET:Not NULL_PTR] UdmGroupKindIndex/UdmEventStrgIndex */
/* VariableGuard | [GUD:RET:IF_GUARDED UdmGroupKindIndex/UdmEventStrgIndex] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC_P2VAR( Dem_UdmEventRecordType, DEM_VAR_SAVED_ZONE, DEM_CODE ) Dem_UdmEventMng_GetEventRecordPtr
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmEventStrgIndex
)
{
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) udmEventRecordPtr;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) eventRecordNum;

    udmEventRecordPtr = NULL_PTR;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
    if( UdmGroupKindIndex < userDefinedMemoryNum )                                          /* [GUD:if]UdmGroupKindIndex */
    {
        eventRecordNum = Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum;      /* [GUD]UdmGroupKindIndex */
        if( UdmEventStrgIndex < eventRecordNum )                                            /* [GUD:if]UdmEventStrgIndex */
        {
            udmEventRecordPtr = &(Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordListStartPtr[UdmEventStrgIndex]);    /* [GUD]UdmGroupKindIndex *//* [GUD]UdmEventStrgIndex *//* [ARYCHK] Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum / 1 / UdmEventStrgIndex */
        }
    }

    return udmEventRecordPtr;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_UdmEventMng_GetEventIdFromRecordData                 */
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
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmEventMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;

    udmEventStrgIndex   =   ( Dem_u16_UdmEventStrgIndexType )RecordIndex;
    udmEventIndex       =   Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex( ( Dem_u16_UdmDemMemKindIndexType )RecordFieldIndex, udmEventStrgIndex );

    retVal  =   Dem_UdmMng_GetEventIdFromUdmEventIndex( udmEventIndex, EventIdPtr );

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
