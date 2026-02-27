/* Dem_ConfigInfo_CmnMem_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_CmnMem/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#endif

#include "Dem_ConfigInfo_Calibration.h"

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

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )  */

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
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>



#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex                */
/* Description   | Converts an event ID to event index.                     */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventId :                                           */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventCtrlIndexPtr :                                */
/*               |        The event index which has been retrieved.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event index retrieving is succe- */
/*               |        ssful.                                            */
/*               |        DEM_IRT_NG : The event index retrieving is faile- */
/*               |        d.                                                */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC )    eventConfigId;
    retVal = DEM_IRT_NG;

    if( EventId >= DEM_EVENT_ID_MIN )
    {
        eventConfigId    =   (Dem_EventParameterConfigIdType)EventId - (Dem_EventParameterConfigIdType)1U;
        retVal           =   Dem_CfgInfoCalib_CnvEventConfigIdToEventCtrlIndex( eventConfigId, EventCtrlIndexPtr );

    }

    /* Returns with the result. */
    return retVal;
}

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent              */
/* Description   | Max number of AllMemory event counts.                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Max number of AllMemory event                            */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventPosType, DEM_CODE ) Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent
( void )
{
    return ( Dem_u16_EventPosType )Dem_PrimaryMemEventConfigureNum;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )    */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent              */
/* Description   | Max number of AllMemory event counts.                    */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Max number of AllMemory event                            */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventPosType, DEM_CODE ) Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent
( void )
{
    VAR( Dem_u16_EventPosType, AUTOMATIC ) retNum;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) primaryEventConfigureNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;

    primaryEventConfigureNum = Dem_PrimaryMemEventConfigureNum;
    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    retNum = ( Dem_u16_EventPosType )primaryEventConfigureNum + ( Dem_u16_EventPosType )udmEventConfigureNum;

    return retNum;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId                    */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_EventIdType                                          */
/*               |        The event ID which has been retrieved.            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /* The specified event index is out of the range ? */
    eventId =   DEM_EVENTID_INVALID;
    (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId ); /* no return check required */          /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */

    /* Return with the result. */
    return eventId;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )    */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId                */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The event ID for retrieving.                      */
/* Return Value  | Dem_EventIdType                                          */
/*               |        The event ID which has been retrieved.            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) primaryEventConfigureNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValUdm;

    eventId =   DEM_EVENTID_INVALID;
    primaryEventConfigureNum    =   ( Dem_u16_EventPosType )Dem_PrimaryMemEventConfigureNum;

    /* The specified event index is out of the range ? */
    if( EventCtrlIndex < primaryEventConfigureNum )
    {
        (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId ); /* no return check required */      /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */
    }
    else
    {
        udmEventIndex   =   DEM_UDMEVENTINDEX_INVALID;
        retValUdm = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );                  /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if( retValUdm == DEM_IRT_OK )
        {
            eventId   =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( udmEventIndex );                                  /* [GUD] udmEventIndex */
        }
    }

    /* Return with the result. */
    return eventId;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */



#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex         */
/* Description   | Converts an event position to event index.               */
/* Preconditions | EventPos < Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent() */
/* Parameters    | [in] EventCtrlIndex :  EventIndex                        */
/* Return Value  | Dem_u08_MemoryKindType                                   */
/*               |               :  Memory kind.                            */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_MemoryKindType, DEM_CODE ) Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) primaryEventConfigureNum;

    primaryEventConfigureNum = ( Dem_u16_EventCtrlIndexType )Dem_PrimaryMemEventConfigureNum;

    if( EventCtrlIndex < primaryEventConfigureNum )
    {
        memKind = DEM_MEMKIND_PRIMARY;
    }
    else
    {
        memKind = DEM_MEMKIND_USERDEFMEM;
    }

    return memKind;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex               */
/* Description   | Converts an event position to event index.               */
/* Preconditions | EventPos < Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent() */
/* Parameters    | [in] EventPos :  EventPosition                           */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    {
        /*  at PrimaryMemory, Dem_u16_EventPosType and Dem_u16_EventCtrlIndexType is same value.    */
        eventCtrlIndex      = ( Dem_u16_EventCtrlIndexType )EventPos;
    }
    return eventCtrlIndex;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF ) */
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex               */
/* Description   | Converts an event position to event index.               */
/* Preconditions | EventPos < Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent() */
/* Parameters    | [in] EventPos :  EventPosition                           */
/*               | [out] MemoryKindPtr :  Memory kind.                      */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) primaryEventConfigureNum;

    primaryEventConfigureNum    =   ( Dem_u16_EventPosType )Dem_PrimaryMemEventConfigureNum;
    if ( EventPos < primaryEventConfigureNum )
    {
        /*  at PrimaryMemory, Dem_u16_EventPosType and Dem_u16_EventCtrlIndexType is same value.    */
        eventCtrlIndex      = ( Dem_u16_EventCtrlIndexType )EventPos;
    }
    else
    {
        eventCtrlIndex      = ( Dem_u16_EventCtrlIndexType )( EventPos - primaryEventConfigureNum );
        eventCtrlIndex     |= ( Dem_u16_EventCtrlIndexType )DEM_EVENT_INDEX_USERDEFMEM_MASK;
    }

    return eventCtrlIndex;
}
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventOperationCycleRef                  */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventIndex < Dem_PrimaryMemEventConfigureNum             */
/* Parameters    | [in] EventCtrlIndex :  EventIndex                        */
/*               | [out] MemoryKindPtr :  Memory kind.                      */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoCmn_GetEventOperationCycleRef
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleRef;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvEventIndex;
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    eventCtrlIndex  =   Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex( EventPos );     /* [GUDCHK:CALLER]EventPos *//* [GUD:RET:IF_GUARDED:EventPos] eventCtrlIndex */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /*  get data.        */
    memKind         =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );     /* [GUDCHK:CALLER]EventPos */
    if ( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  user defined memory.        */
        udmEventIndex = DEM_UDMEVENTINDEX_INVALID;
        /* Convert EventIndex to udmEventIndex */
        retCnvEventIndex = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );   /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if( retCnvEventIndex == DEM_IRT_OK )
        {
            operationCycleRef   =   Dem_CfgInfoUdm_GetEventOperationCycleRef( udmEventIndex );                  /* [GUD] udmEventIndex */
        }
        else
        {
            operationCycleRef = DEM_OPERATION_CYCLE_INDEX_INVALID;
        }
    }
    else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    {
        /*  primary memory.     */
        operationCycleRef   =   Dem_CfgInfoPm_GetEventOperationCycleRef( eventCtrlIndex );  /* [GUDCHK:CALLER]EventPos */
    }

    return operationCycleRef;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventHealingAgingCycleRef               */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum + Dem_UdmE- */
/*               | ventConfigureNum                                         */
/* Parameters    | [in] EventPos :  EventPos                                */
/*               | [out] MemoryKindPtr :  Memory kind.                      */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoCmn_GetEventHealingAgingCycleRef
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleRef;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvEventIndex;
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    eventCtrlIndex  =   Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex( EventPos );     /* [GUDCHK:CALLER]EventPos *//* [GUD:RET:IF_GUARDED:EventPos] eventCtrlIndex */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    memKind         =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );     /* [GUDCHK:CALLER]EventPos */
    if ( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  user defined memory.        */
        udmEventIndex = DEM_UDMEVENTINDEX_INVALID;
        /* Convert EventIndex to udmEventIndex */
        retCnvEventIndex = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );   /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if( retCnvEventIndex == DEM_IRT_OK )
        {
            /* get data from OperationCycleRef.  */
            operationCycleRef   =   Dem_CfgInfoUdm_GetEventOperationCycleRef( udmEventIndex );                  /* [GUD] udmEventIndex */
        }
        else
        {
            operationCycleRef = DEM_OPERATION_CYCLE_INDEX_INVALID;
        }
    }
    else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    {
        /*  primary memory.     */
        operationCycleRef = Dem_CfgInfoPm_GetEventHealingAgingCycleRef( eventCtrlIndex );       /* [GUDCHK:CALLER]EventPos */
    }
    return operationCycleRef;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoCmn_GetDTCStatusAvailabilityMask              */
/* Description   | Gets the DTC Status availability mask.                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusMaskPtr :                                 */
/*               |        The value DTCStatusMask indicates the supported - */
/*               |        DTC status bits from the Dem.All supported infor- */
/*               |        mation is indicated by setting the corresponding  */
/*               |         status bit to 1.See ISO14229-1.                  */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCmn_GetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin                           /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /*  DTCOrigin judge   */
    if (( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        /*  UserDefinedMemory       */
        retVal  =   Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask_ByDTCOrigin( DTCStatusMaskPtr, DTCOrigin );
    }
    else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    {
        /*  PrimaryMemory           */
        Dem_CfgInfoPm_GetDTCStatusAvailabilityMask( DTCStatusMaskPtr );
        retVal  =   DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoCmm_GetExDataClassRef                         */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | EventCtrlIndex < Dem_PrimaryMemEventConfigureNum + Dem_UdmE- */
/*               | ventConfigureNum                                         */
/* Parameters    | [in] EventCtrlIndex :  EventCtrlIndex                    */
/*               | [out] ExDataClassRefPtr :                                */
/*               | [out] ExDataClassMaxNumPtr                               */
/*               |     Number of Configured ExtendData class                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoCmm_GetExDataClassRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassMaxNumPtr
)
{
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */

    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvEventIndex;

    memKind  =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );

    if ( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  user defined memory.        */
        udmEventIndex = DEM_UDMEVENTINDEX_INVALID;
        /* Convert EventIndex to udmEventIndex */
        retCnvEventIndex = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );   /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
        if( retCnvEventIndex == DEM_IRT_OK )
        {
            Dem_CfgInfoUdm_GetExDataClassRef( udmEventIndex, ExDataClassRefPtr );                               /* [GUD] udmEventIndex */
        }
        else
        {
            /*  invalid memory.     */
            *ExDataClassRefPtr  =   DEM_EXDATACLASSINDEX_INVALID;
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    {
        /*  primary memory.     */
        Dem_CfgInfoPm_GetExDataClassRef( EventCtrlIndex, ExDataClassRefPtr );
    }
    /*  set max number.     */
    *ExDataClassMaxNumPtr =   Dem_ExDataClassNum;

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
