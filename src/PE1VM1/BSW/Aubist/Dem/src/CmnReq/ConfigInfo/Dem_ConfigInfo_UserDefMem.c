/* Dem_ConfigInfo_UserDefMem_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_UserDefMem/CODE                            */
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
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"

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

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex          */
/* Description   | Converts an Event Index to Udm event index.              */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event Index for retrieving.                   */
/*               | [out] UdmEventIndexPtr :                                 */
/*               |        The event index which has been retrieved.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event index retrieving is succe- */
/*               |        ssful.                                            */
/*               |        DEM_IRT_NG : The event index retrieving is faile- */
/*               |        d.                                                */
/* Notes         | none                                                     */
/* Func History  | name(v3-0-0) : Dem_Data_ConvertEventIdToIndex            */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] UdmEventIndexPtr                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) tmpUdmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    /* Sets the return value to NG. */
    retVal = DEM_IRT_NG;

    if( EventCtrlIndex >= DEM_EVENT_INDEX_USERDEFMEM_MASK ) /* [GUD:if]EventCtrlIndex */
    {
        /* Mask UserDefinedMemory Definition Bit. (0x8000) */
        tmpUdmEventIndex = EventCtrlIndex & ~( (Dem_u16_EventCtrlIndexType) DEM_EVENT_INDEX_USERDEFMEM_MASK);

        /* Check Range of UserDefMem Event Index. */
        if( tmpUdmEventIndex < eventConfigureNum )  /* [GUD:if]tmpUdmEventIndex */
        {
            /* input the UserDefMem Event Index. */
            *UdmEventIndexPtr = tmpUdmEventIndex;
            retVal = DEM_IRT_OK;
        }
    }
    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvEventPosToUdmEventIndex                */
/* Description   | Converts an Event Index to Udm event index.              */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event Index for retrieving.                   */
/*               | [out] UdmEventIndexPtr :                                 */
/*               |        The event index which has been retrieved.         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event index retrieving is succe- */
/*               |        ssful.                                            */
/*               |        DEM_IRT_NG : The event index retrieving is faile- */
/*               |        d.                                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvEventPosToUdmEventIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;

    retVal = DEM_IRT_NG;

    /*  convert event position to event index       */
    eventCtrlIndex  =   Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex( EventPos );
    memKind         =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );

    if ( memKind != DEM_MEMKIND_PRIMARY )
    {
        (void)Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, UdmEventIndexPtr );    /* no return check required */    /* [GUD:RET:DEM_IRT_OK] UdmEventIndexPtr */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvUdmEventIndexToEventId                 */
/* Description   | Converts an Event Index to Udm event index.              */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event Index for retrieving.                   */
/*               |          convert by Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex().   */
/* Return Value  | Dem_u16_EventCtrlIndexType  EventIndex                   */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToEventCtrlIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    eventCtrlIndex      =   ( Dem_u16_EventCtrlIndexType )UdmEventIndex;
    eventCtrlIndex      =   eventCtrlIndex | ( Dem_u16_EventCtrlIndexType )DEM_EVENT_INDEX_USERDEFMEM_MASK;

    return eventCtrlIndex;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvUdmEventIndexToEventId                 */
/* Description   | Converts an Event Index to Udm event index.              */
/* Preconditions | The specified event ID has been already registered.      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u16_EventCtrlIndexType  EventIndex                   */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToEventId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal  =   DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;

    /* The specified event index is out of the range ? */
    if( UdmEventIndex < eventConfigureNum ) /* [GUD:if]tmpUdmEventIndex */
    {
        /* Add 1 to the EventIndex and stores it in the specified EventId storage area. */
        *EventIdPtr   =   Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );

        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }

    /* Return with the result. */
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex       */
/* Description   | Converts an Udm event index to Udm event storage index.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u16_UdmEventStrgIndexType                            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED: UdmGroupKindIndex/UdmEventIndex ] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmEventStrgIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;

    udmEventStrgIndex = UdmEventIndex - Dem_UserDefinedMemoryGroupTable[ UdmGroupKindIndex ].DemSearchStartIndexOfEventParameterTable;  /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return udmEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex       */
/* Description   | Converts an Udm storage event index to Udm event index.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Parameters    | [in] UdmStrgEventIndex :                                 */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u16_UdmEventIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:IF_GUARDED:UdmGroupKindIndex/UdmStrgEventIndex] ReturnValue */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmStrgEventIndex
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;

    /*  get start of udm event index.           */
    udmEventIndex       =   Dem_UserDefinedMemoryGroupTable[ UdmGroupKindIndex ].DemSearchStartIndexOfEventParameterTable;  /* [GUDCHK:CALLER]UdmGroupKindIndex */
    udmEventIndex       =   udmEventIndex + ( Dem_u16_UdmEventIndexType )UdmStrgEventIndex;

    return udmEventIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask_ByDTCOrigin  */
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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask_ByDTCOrigin
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) loopMaxNum;
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginNoPrefix;

    retVal = DEM_IRT_NG;
    loopMaxNum = Dem_UserDefinedMemoryInfoNum;
    DTCOriginNoPrefix = DTCOrigin &~ DEM_DTC_ORIGIN_USERDEFINED_MEMORY;

    for( loopCnt = (Dem_u08_UdmMemoryInfoTableIndexType)0U; loopCnt < loopMaxNum; loopCnt++ )   /* [GUD:for]loopCnt */
    {
        if( DTCOriginNoPrefix == (Dem_DTCOriginType)Dem_UserDefinedMemoryInfoTable[loopCnt].DemUserDefinedMemoryIdentifier )    /* [GUD]loopCnt */
        {
            *DTCStatusMaskPtr = Dem_UserDefinedMemoryInfoTable[loopCnt].DemDtcStatusAvailabilityMask;   /* [GUD]loopCnt */
            retVal = DEM_IRT_OK;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask              */
/* Description   | Gets the DTC Status availability mask.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/* Return Value  | Dem_UdsStatusByteType                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;

    dtcStatusAvailabilityMask = Dem_UserDefinedMemoryInfoTable[ UdmInfoTableIndex ].DemDtcStatusAvailabilityMask;   /* [GUDCHK:CALLER]UdmInfoTableIndex */

    return dtcStatusAvailabilityMask;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory            */
/* Description   | Get the start index of MemorySelection.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Return Value  | Dem_u16_UdmEventIndexType                                */
/*               |        StartIndex                                        */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) retVal;

    retVal = (Dem_u16_UdmEventIndexType)Dem_UserDefinedMemoryGroupTable[UdmGroupKindIndex].DemSearchStartIndexOfEventParameterTable;    /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory   */
/* Description   | Get the End index of MemorySelection.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Return Value  | Dem_u16_UdmEventIndexType                                */
/*               |        EndIndex                                          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) retVal;

    retVal = (Dem_u16_UdmEventIndexType)( Dem_UserDefinedMemoryGroupTable[UdmGroupKindIndex].DemConfigureEventNumOfMemorySelection );   /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetMaxNumberOfEventEntry                  */
/* Description   | Get MaxNumberOfEventEntry.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/*               |        MaxNumberOfEventEntry                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberOfEventEntry
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) maxNumberOfEventEntryUserDefined;

    maxNumberOfEventEntryUserDefined = Dem_UserDefinedMemoryGroupTable[ UdmGroupKindIndex ].DemMaxNumberEventEntryUserDefined;  /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return maxNumberOfEventEntryUserDefined;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetMaxNumberOfFreezeFramePerDTC           */
/* Description   | Get MaxNumberOfEventEntry.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The Index of Dem_UserDefinedMemoryGroupTable      */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/*               |        MaxNumberOfEventEntry                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberOfFreezeFramePerDTC
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberOfFreezeFrameUserDefined;

    maxNumberOfFreezeFrameUserDefined = Dem_UserDefinedMemoryGroupTable[ UdmGroupKindIndex ].DemMaxNumberFreezeFrameUserDefinedPerDTC;  /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return maxNumberOfFreezeFrameUserDefined;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryIdentifier            */
/* Description   | Gets the User deined memory identifier.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event Index for retrieving.                   */
/* Return Value  | uint8 :                                                  */
/*               |        The memory identifier which has been retrieved.   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( uint8, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( uint8, AUTOMATIC ) memId;
    VAR( Dem_DTCOriginType, AUTOMATIC ) memIdOrigin;

    /*  get udmInfoTableIndex        */
    udmInfoTableIndex    =   Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );  /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */

    /*  get memory identifier   */
    memIdOrigin      =   Dem_UserDefinedMemoryInfoTable[ udmInfoTableIndex ].DemUserDefinedMemoryIdentifier;    /* [GUDCHK:CALLER]UdmEventIndex */
    memId            =   ( uint8 )( memIdOrigin & DEM_DTC_ORIGIN_MEMORYIDENTIFIER_MASK );

    return memId;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetEventOperationCycleRef                 */
/* Description   | GetData by EventIndex                                    */
/* Preconditions | UdmEventIndex < Dem_UdmMemEventConfigureNum              */
/* Parameters    | [in] EventIndex :  EventIndex                            */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetEventOperationCycleRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleRef;

    operationCycleRef = Dem_UdmEventParameterTable[ UdmEventIndex ].DemOperationCycleRef;   /* [GUDCHK:CALLER]UdmEventIndex */

    return operationCycleRef;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByUdmEventIndex   */
/* Description   | Gets UserDefinedMemory type.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u08_UserDefinedMemoryType :                          */
/*               |        UserDefinedMemory type.                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByUdmEventIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;

    /*  get udmInfoTableIndex        */
    udmInfoTableIndex    =   Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );  /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */

    /*  get memory identifier   */
    memType         =   Dem_UserDefinedMemoryInfoTable[ udmInfoTableIndex ].DemMemoryType;  /* [GUDCHK:CALLER]UdmEventIndex */

    return memType;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind         */
/* Description   | Gets UserDefinedMemory type.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u08_UserDefinedMemoryType :                          */
/*               |        UserDefinedMemory type.                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;

    /*  get memory identifier   */
    memType         =   Dem_UserDefinedMemoryInfoTable[ UdmInfoTableIndex ].DemMemoryType;  /* [GUDCHK:CALLER]UdmInfoTableIndex */

    return memType;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin_      */
/* Description   | Gets UserDefinedMemory type.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        DTCOrigin                                         */
/* Parameters    | [in] UdmInfoTableIndexPtr :                              */
/*               |        UdmInfoTableIndex                                 */
/* Return Value  | Dem_u08_UserDefinedMemoryType :                          */
/*               |        UserDefinedMemory type.                           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not DEM_MEMORYTYPE_INVALID] UdmInfoTableIndexPtr */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin_InAllUdm(v5-3-0). */
/*               | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC, AUTOMATIC ) UdmInfoTableIndexPtr
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) loopMaxNum;
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginNoPrefix;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;

    memType    = DEM_MEMORYTYPE_INVALID;
    loopMaxNum = Dem_UserDefinedMemoryInfoNum;

    /* Checks the specified DTCOrigin type. */
    if( ( DTCOrigin & ( Dem_DTCOriginType )DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == ( Dem_DTCOriginType )DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
    {
        DTCOriginNoPrefix = DTCOrigin &~ DEM_DTC_ORIGIN_USERDEFINED_MEMORY;

        for( loopCnt = (Dem_u08_UdmMemoryInfoTableIndexType)0U; loopCnt < loopMaxNum; loopCnt++ )   /* [GUD:for]loopCnt */
        {
            if( DTCOriginNoPrefix == (Dem_DTCOriginType)Dem_UserDefinedMemoryInfoTable[loopCnt].DemUserDefinedMemoryIdentifier )    /* [GUD:if]loopCnt */
            {
                memType               = Dem_UserDefinedMemoryInfoTable[loopCnt].DemMemoryType;  /* [GUD]loopCnt */
                *UdmInfoTableIndexPtr = loopCnt;
                break;
            }
        }
    }

    return memType;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetEventDisplacementStrategy              */
/* Description   | Gets EventDisplacementStrategy type.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/*               |        The event Index for retrieving.                   */
/* Return Value  | Dem_u08_EventDisplacementStrategyType :                  */
/*               |        EventDisplacementStrategy type.                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_EventDisplacementStrategyType, DEM_CODE ) Dem_CfgInfoUdm_GetEventDisplacementStrategy
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_EventDisplacementStrategyType, AUTOMATIC ) eventDispStrategy;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupkindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /*  get memory identifier   */
    memType         =   Dem_UserDefinedMemoryInfoTable[ UdmInfoTableIndex ].DemMemoryType;  /* [GUDCHK:CALLER]UdmInfoTableIndex */

    eventDispStrategy           =   DEM_DISPLACEMENT_NONE;
    if ( memType == DEM_MEMORYTYPE_ASYNCEVENT )
    {
        /* get udm group index */
        udmGroupkindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( UdmInfoTableIndex, UdmEventIndex );

        if( udmGroupkindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupkindIndex */
        {
            eventDispStrategy = Dem_UserDefinedMemoryGroupTable[ udmGroupkindIndex ].DemEventDisplacementStrategy;  /* [GUD]udmGroupkindIndex */
        }
    }

    return eventDispStrategy;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_TriggerInitMForEFnc                       */
/* Description   | Calls callback function "InitMonitorForEvent" correspon- */
/*               | ding to specified event index.                           */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] InitMonitorReason :                                 */
/*               |        The reasion of initializing monitor.              */
/*               | [out] ResultOfCallbackPtr :                              */
/*               |        The result of calling callback function.          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/* Func History  | name(v3-0-0) : Dem_Data_TriggerInitMForEFnc              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_TriggerInitMForEFnc
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_InitMonitorReasonType, AUTOMATIC ) InitMonitorReason,
    P2VAR( Std_ReturnType, AUTOMATIC, AUTOMATIC ) ResultOfCallbackPtr
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;

    /* Initializes the result of callback to OK. */
    resultOfCallback = E_OK;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    /* Checks the specified udmevent ID be within the range. */
    if( UdmEventIndex < udmEventConfigureNum )  /* [GUD:if]UdmEventIndex */
    {
        /* Within the range. */

        /* Checks the presence of the callback function pointer corresponding to the specified event index. */
        if( Dem_UdmEventParameterTable[UdmEventIndex].DemCallbackInitMForEFnc != NULL_PTR ) /* [GUD]UdmEventIndex */
        {
#ifndef JGXSTACK
            /* Calls the callback function corresponding to the specified event index. */
            resultOfCallback = Dem_UdmEventParameterTable[UdmEventIndex].DemCallbackInitMForEFnc( InitMonitorReason );  /* [GUD]UdmEventIndex */
#else /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
        else
        {
           /* no processing. */
        }

        /* Stores the result of the callback function to the specified parameter. */
        *ResultOfCallbackPtr = resultOfCallback;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_TriggerEventStatusChangedFnc              */
/* Description   | Calls callback function "EventStatusChanged" correspond- */
/*               | ing to specified event index.                            */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] OldDTCStatus :                                      */
/*               |        The UDS DTC status byte before updating.          */
/*               | [in] NewDTCStatus :                                      */
/*               |        The UDS DTC status byte after updating.           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_TriggerEventStatusChangedFnc
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,          /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    P2CONST( AB_83_ConstV Dem_UdmEventParameterType, AUTOMATIC, DEM_CONFIG_DATA ) eventParameterPtr;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    oldDTCStatusTmp =   OldDTCStatus;
    newDTCStatusTmp =   NewDTCStatus;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

    if( oldDTCStatusTmp != newDTCStatusTmp )
    {
        /* Gets an event ID by event index. */
        eventId = Dem_CfgInfoCalib_CnvUdmEventIndexToEventId( UdmEventIndex );      /* [GUDCHK:CALLER]UdmEventIndex */

        /* Holds the event table pointed to by the specified event index. */
        eventParameterPtr = &Dem_UdmEventParameterTable[ UdmEventIndex ];           /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:CFG:IF_GUARDED: UdmEventIndex ]eventParameterPtr */

        if( eventParameterPtr->DemCallbackEventStatusChangedFnc != NULL_PTR )       /* [GUDCHK:CALLER]UdmEventIndex */
        {
#ifndef JGXSTACK
            /* Calls callback EventStatusChange corresponding to the specified event ID and status. */
            eventParameterPtr->DemCallbackEventStatusChangedFnc( eventId, oldDTCStatusTmp, newDTCStatusTmp );
#else /* JGXSTACK */
                /* user-defined */
#endif /* JGXSTACK */
        }
        else
        {
            /* no processing. */
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex        */
/* Description   | Gets UserDefinedMemory type.                             */
/* Preconditions | none                                                     */
/* Parameters    | [In] UdmInfoTableIndex :                                 */
/*               |        Index of Dem_UserDefinedMemoryInfoTable           */
/* Parameters    | [Out] UdmGroupKindIndexStartPtr :                        */
/*               |        Start index of udm group table in Dem_UserDefine- */
/*               |        dMemoryInfoTable                                  */
/*               | [Out] UdmGroupKindIndexNumPtr :                          */
/*               |        Num of udm group table in Dem_UserDefinedMemoryI- */
/*               |        nfoTable                                          */
/* Return Value  | Dem_u16_UdmDemMemKindIndexType :                         */
/*               |        UserDefinedMemory kind index.                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,            /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexStartPtr,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexNumPtr
)
{
    /* Get udm group index. */
    *UdmGroupKindIndexStartPtr = Dem_UserDefinedMemoryInfoTable[ UdmInfoTableIndex ].DemUserDefinedMemoryKindIndexStart;    /* [GUDCHK:CALLER]UdmInfoTableIndex */
    *UdmGroupKindIndexNumPtr   = Dem_UserDefinedMemoryInfoTable[ UdmInfoTableIndex ].DemUserDefinedMemoryKindIndexNum;      /* [GUDCHK:CALLER]UdmInfoTableIndex */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex */
/* Description   | Gets UserDefinedMemory type.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmInfoTableIndex :                                 */
/*               |        UdmInfoTableIndex                                 */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        UdmEventIndex                                     */
/* Return Value  | Dem_u16_UdmDemMemKindIndexType :                         */
/*               |        UserDefinedMemory kind index.                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_UdmDemMemKindIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) retUdmGroupkindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupkindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexEnd;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexStart;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexEnd;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndexNum;

    udmInfoTableIndexNum = Dem_UserDefinedMemoryInfoNum;
    retUdmGroupkindIndex = DEM_UDMTABLEINDEX_INVALID;

    if( UdmInfoTableIndex < udmInfoTableIndexNum )  /* [GUD:if]UdmInfoTableIndex */
    {
        /* Get udm group index. */
        Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( UdmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );

        /* Set loop max num */
        udmGroupKindIndexEnd = udmGroupKindIndexStart + udmGroupKindIndexNum;

        /* Loop by udm group */
        for( udmGroupkindIndex = udmGroupKindIndexStart; udmGroupkindIndex < udmGroupKindIndexEnd; udmGroupkindIndex++ )    /* [GUD:for]udmGroupkindIndex */
        {
            udmEventIndexStart   = Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory( udmGroupkindIndex );
            udmEventIndexNum = Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory( udmGroupkindIndex );
            udmEventIndexEnd = udmEventIndexStart + udmEventIndexNum;

            /* Check the event is exist in the udm group. */
            if( ( UdmEventIndex >= udmEventIndexStart ) && ( UdmEventIndex < udmEventIndexEnd ) )
            {
                retUdmGroupkindIndex = udmGroupkindIndex;
                break;
            }
        }
    }

    return retUdmGroupkindIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex     */
/* Description   | Gets UserDefinedMemoryInfoTableIndex.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The udm group kind Index.                         */
/* Return Value  | Dem_u08_UdmMemoryInfoTableIndexType :                    */
/*               |        UserDefinedMemory table index.                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    /*  get udm info table index   */
    udmInfoTableIndex = Dem_UserDefinedMemoryGroupTable[ UdmGroupKindIndex ].DemUserDefinedMemoryInfoTableIndex;    /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return udmInfoTableIndex;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

