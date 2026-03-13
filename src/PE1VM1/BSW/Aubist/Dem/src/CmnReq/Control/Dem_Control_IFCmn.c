/* Dem_Control_IFCmn_c(v5-8-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_IFCmn/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Udm_DataAvl.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_Udm_Data.h"
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
#include "../../../inc/Dem_Mm_MM_RecordInfo.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetEventStatus                          */
/* Description   | Gets status of DTC by event ID from event record.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] UDSStatusBytePtr :                                 */
/*               |        UDS DTC status byte of the requested event        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of event status was successful   */
/*               |        DEM_IRT_NG : get of event status failed           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) UDSStatusBytePtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventIdRange;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) udsStatus;
    VAR( boolean, AUTOMATIC ) availableStatus;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    udmEventIndex        = DEM_UDMEVENTINDEX_INVALID;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    eventCtrlIndex  =   DEM_EVENTCTRLINDEX_INVALID;
    udsStatus       =   (Dem_UdsStatusByteType)0U;
    retVal          =   DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Check EventID Range. */
        retEventIdRange = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventID, &eventCtrlIndex );

        if( retEventIdRange == DEM_IRT_OK )
        {
            availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );

            if( availableStatus == (boolean)TRUE )
            {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
                /* check eventIndex kind. */
                memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
                if( memKind != DEM_MEMKIND_PRIMARY )
                {
                    /*  checuserdefinememory event.     */
                    retTempVal = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex ); /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
                    if( retTempVal == DEM_IRT_OK )
                    {
                        /* Get udm table info index by udm event index. */
                        udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( udmEventIndex );                   /* [GUD]udmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */

                        /* Get udm group index by udm event index. */
                        udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, udmEventIndex );  /* [GUD] udmEventIndex */

                        if( udmGroupKindIndex < userDefinedMemoryNum )          /* [GUD:if]udmGroupKindIndex */
                        {
                            /*  userdefinedmemory.          */
                            /*--------------------------------------------------------------------------*/
                            /* Need to get exclusive [SchM_Enter_Dem_Udm_<ShortName>_EventMemory].      */
                            /* These are the reasons why this function needs to get exclusive.          */
                            /*  - This function call [DataMng] function directory.                      */
                            /*  - This function called from SW-C/Dcm context.                           */
                            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
#ifndef JGXSTACK
                            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();  /* [GUD]udmGroupKindIndex *//* waits completion of updating Diag record data by Dem_MainFunction.      */
                            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();   /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
                            Dem_UdmExcEnterFnc_ForStack();
                            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
                            /*--------------------------------------------------------------------------*/
                            Dem_UdmDTC_GetDTCStatusOfEvent( udmEventIndex , &udsStatus );              /* [GUD] udmEventIndex */
                            retTempVal = DEM_IRT_OK;
                        }
                        else
                        {
                            retTempVal = DEM_IRT_NG;
                        }
                    }
                }
                else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
                {
                    /*  primary memory.     */
                    /*--------------------------------------------------------------------------*/
                    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                    /* These are the reasons why this function needs to get exclusive.          */
                    /*  - This function call [DataMng] function directory.                      */
                    /*  - This function called from SW-C/Dcm context.                           */
                    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                    SchM_Exit_Dem_EventMemory();
                    /*--------------------------------------------------------------------------*/
                    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                    retTempVal = Dem_DTC_GetDTCStatusOfEvent( eventStrgIndex, &udsStatus );
                }

                if( retTempVal == DEM_IRT_OK )
                {
                    /*------------------------------------------*/
                    /*  convert to output statusOfDTC.          */
                    /*------------------------------------------*/
                    *UDSStatusBytePtr = Dem_DTC_CnvDTCStatus_ForOutput( udsStatus );
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetEventUdsStatusHistory                */
/* Description   | Gets status of DTC by event ID from event record.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] UDSStatusHistoryBytePtr :                          */
/*               |        UDS DTC status history byte of the requested event*/
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of event status was successful   */
/*               |        DEM_IRT_NG : get of event status failed           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC, AUTOMATIC ) UDSStatusHistoryBytePtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventIdRange;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )    extendStatusOfDTC;
    VAR( boolean, AUTOMATIC ) availableStatus;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    eventCtrlIndex      =   DEM_EVENTCTRLINDEX_INVALID;
    retVal          =   DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Check EventID Range. */
        retEventIdRange = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventID, &eventCtrlIndex );

        if( retEventIdRange == DEM_IRT_OK )
        {
            availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );

            if( availableStatus == (boolean)TRUE )
            {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
                /* check eventIndex kind. */
                memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
                if( memKind != DEM_MEMKIND_PRIMARY )
                {
                    /*  UserDefinedMemory : not supported.      */
                }
                else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
                {
                    /*  primary memory.     */
                    /*--------------------------------------------------------------------------*/
                    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
                    /* These are the reasons why this function needs to get exclusive.          */
                    /*  - This function call [DataMng] function directory.                      */
                    /*  - This function called from SW-C/Dcm context.                           */
                    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
                    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
                    SchM_Exit_Dem_EventMemory();
                    /*--------------------------------------------------------------------------*/
                    extendStatusOfDTC   =   DEM_DTCSTATUSEX_BYTE_ALL_OFF;
                    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );            /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                    (void)Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendStatusOfDTC ); /* no return check required */

                    *UDSStatusHistoryBytePtr    =   ((Dem_UdsStatusHistoryByteType)extendStatusOfDTC & DEM_DTCSTATUSEX_BYTE_MASK_HISTORY );

                    retVal          =   DEM_IRT_OK;

                }
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetDTCOfEvent                           */
/* Description   | Gets the DTC of an event.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alue.                                             */
/*               | [out] DTCOfEvent :                                       */
/*               |        Receives the DTC value in respective format retu- */
/*               |        rned by this function. If the return value of th- */
/*               |        e function is other than E_OK this parameter doe- */
/*               |        s not contain valid data.                         */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of DTC was successful                  */
/*               |        E_NOT_OK : the call was not successful DEM_E_NO_- */
/*               |        DTC_AVAILABLE                                     */
/*               |        DEM_E_NO_DTC_AVAILABLE : there is no DTC configu- */
/*               |        red in  the requested format                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetDTCOfEvent
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCOfEventPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventIdRange;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( boolean, AUTOMATIC ) availableStatus;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;

    udmEventIndex   = DEM_UDMEVENTINDEX_INVALID;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    eventCtrlIndex      = DEM_EVENTCTRLINDEX_INVALID;
    retVal          = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Check EventID Range. */
        retEventIdRange = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventID, &eventCtrlIndex );

        if( retEventIdRange == DEM_IRT_OK )
        {
            retTempVal = Dem_CfgInfoPm_CheckDTCFormat( DTCFormat );
            if( retTempVal == DEM_IRT_OK )
            {
                availableStatus = Dem_DataAvl_GetEvtAvlCommon( eventCtrlIndex );

                if( availableStatus == (boolean)TRUE )
                {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
                    /* check eventIndex kind. */
                    memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );

                    if( memKind != DEM_MEMKIND_PRIMARY )
                    {
                        /* Convert eventIndex to UdmEventIndex. */
                        retTempVal = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );     /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
                        if( retTempVal == DEM_IRT_OK )
                        {
                            retTempVal = Dem_UdmDataAvl_GetDTCByUdmEventIndex( udmEventIndex, DTCFormat, DTCOfEventPtr );   /* [GUD] udmEventIndex */
                        }
                    }
                    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
                    {
                        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
                        retTempVal = Dem_DataAvl_GetDTCByEventStrgIndex( eventStrgIndex, DTCFormat, DTCOfEventPtr );
                    }

                    if( retTempVal == DEM_IRT_OK )
                    {
                        retVal = DEM_IRT_OK;
                    }
                    else if( retTempVal == DEM_IRT_NODATAAVAILABLE )
                    {
                        retVal = DEM_IRT_NODATAAVAILABLE;
                    }
                    else
                    {
                        /*  no process.         */
                        /*  DEM_IRT_NG.         */
                    }
                }
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetNumberOfEventMemoryEntries           */
/* Description   | Gets NumberOfEventMemoryEntries from event memory relat- */
/*               | ed record.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        select the source memory the number of entries s- */
/*               |        hall be read from                                 */
/*               | [out] NumberOfEventMemoryEntriesPtr :                    */
/*               |        Number of entries currently stored in the reques- */
/*               |        ted event memory                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal          = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        if( DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            retTempVal = Dem_UdmControl_GetNumberOfEventMemoryEntries( DTCOrigin, NumberOfEventMemoryEntriesPtr );
        }
        else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
        {
            retTempVal = Dem_Data_GetNumberOfEventMemoryEntries( DTCOrigin, NumberOfEventMemoryEntriesPtr );
        }

        if( retTempVal == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_SetEvtAvl                               */
/* Description   | Set the available status of a specific Event.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] AvailableStatus :                                   */
/*               |        This parameter specifies whether the respective   */
/*               |        Event shall be available (TRUE) or not (FALSE).   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Change of available status not       */
/*               |                     accepted.                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_SetEvtAvl
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */

    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retVal      = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterPreInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Check EventID Range. */
        retTempVal = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );

        if( retTempVal == DEM_IRT_OK )
        {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
            /* check eventIndex kind. */
            memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );

            if( memKind != DEM_MEMKIND_PRIMARY )
            {
                retTempVal  =   Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );      /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
                if( retTempVal == DEM_IRT_OK )
                {
                    retVal = Dem_UdmDataAvl_SetEvtAvl( udmEventIndex, AvailableStatus );        /* [GUD] udmEventIndex */
                }
            }
            else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
            {
                retVal = Dem_Control_SetEvtAvl( EventId , AvailableStatus );
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetUserDefinedMemoryIdentifier          */
/* Description   | Get memory identifier.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] MemoryIdentifierPtr :                              */
/*               |        Pointer to the area to get memoryid.              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) MemoryIdentifierPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
    VAR( boolean, AUTOMATIC ) availableStatus;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
        if( retTempVal == DEM_IRT_OK )
        {
            memKind  =   Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( eventCtrlIndex );
            if( memKind != DEM_MEMKIND_PRIMARY )
            {
                retTempVal = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( eventCtrlIndex, &udmEventIndex );     /* [GUD:RET:DEM_IRT_OK] udmEventIndex */
                if( retTempVal == DEM_IRT_OK )
                {
                    availableStatus = Dem_UdmDataAvl_GetEvtAvl( udmEventIndex );                                    /* [GUD] udmEventIndex */
                    if( availableStatus == (boolean)TRUE )
                    {
                        *MemoryIdentifierPtr = Dem_CfgInfoUdm_GetUserDefinedMemoryIdentifier( udmEventIndex );      /* [GUD] udmEventIndex */
                        retVal = DEM_IRT_OK;
                    }
                }
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetRecordInfoByNvMBlockId               */
/* Description   | Get record information by NvM block Id.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] RecordKindPtr :                                    */
/*               |        Pointer to the area to get record kind.           */
/*               | [out] EventIdPtr :                                       */
/*               |        Pointer to the area to get eventid.               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetRecordInfoByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_RecordKindType, AUTOMATIC, AUTOMATIC ) RecordKindPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal  =   Dem_MM_GetRecordInfoByNvMBlockId( BlockId, RecordKindPtr, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ControlIFCmn_GetUserDefinedMemoryFreezeFrameRecordNumber */
/* Description   | Gets freeze frame data by DTC and the record number fro- */
/*               | m freeze frame record.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [out] RecordNumBufferPtr :                               */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] RecordNumPtr :                                  */
/*               |        the actual number of written data bytes           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_NODATAAVAILABLE                           */
/*               |          : DTCOrigin is not output support.              */
/*               |        DEM_IRT_WRONG_DTCORIGIN : wrong DTC origin        */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Record number is no- */
/*               |        t supported by configuration and therefore inval- */
/*               |        id                                                */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/*               |        DEM_IRT_NG : condition error.                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ControlIFCmn_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    retVal          = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
            memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex );  /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
            if( memType != DEM_MEMORYTYPE_INVALID )
            {
                retVal = Dem_UdmControl_GetUserDefinedMemoryFreezeFrameRecordNumber( DTCValue, DTCOrigin, RecordNumBufferPtr, RecordNumPtr );
            }
            else
            {
                retVal = DEM_IRT_WRONG_DTCORIGIN;
            }
        }
        else
        {
            retVal  =   DEM_IRT_WRONG_DTCORIGIN;
        }
    }

    return retVal;
}
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/


