/* Dem_If_GetEventStatus_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_OBD/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Pm_Control.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_GetEventUdsStatus                                    */
/* Description   | Gets the current extended event status of an event.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] UDSStatusByte :                                    */
/*               |        UDS DTC status byte of the requested event (refe- */
/*               |        r to chapter "Status bit support"). If the retur- */
/*               |        n value of the function call is E_NOT_OK, this p- */
/*               |        arameter does not contain valid data.             */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of event status was successful         */
/*               |        E_NOT_OK : get of event status failed             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventUdsStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusByte
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) udsStatus;

    retVal = E_NOT_OK;

    if( UDSStatusByte != NULL_PTR )
    {
        udsStatus = (Dem_UdsStatusByteType)0U;    /*  out paramter.   */
        internalReturnValue = Dem_ControlIFCmn_GetEventStatus( EventId , &udsStatus );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *UDSStatusByte = udsStatus; /*  set value to out parameter. */
                retVal = E_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            default:
                /* No Process */
                break;
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_GetEventUdsStatusHistory                             */
/* Description   | Gets the current extended event status of an event.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] UDSStatusHistoryBytePtr :                          */
/*               |        UDS DTC status history.                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of event status was successful         */
/*               |        E_NOT_OK : get of event status failed             */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusHistoryBytePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) udsStatusHistory;

    retVal = E_NOT_OK;

    if( UDSStatusHistoryBytePtr != NULL_PTR )
    {
        udsStatusHistory = (Dem_UdsStatusHistoryByteType)0U;    /*  out paramter.   */
        internalReturnValue = Dem_ControlIFCmn_GetEventUdsStatusHistory( EventId , &udsStatusHistory );

        /* Convert return value */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            *UDSStatusHistoryBytePtr = udsStatusHistory; /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
/****************************************************************************/
/* Function Name | Dem_GetMonitorStatus                                     */
/* Description   | Get MonitorStatus                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventId :                                          */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] MonitorStatus    :                                 */
/*               |          Monitor status byte of the requested event for  */
/*               |          FiM.                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA ) MonitorStatus
)
{
    VAR( Std_ReturnType, AUTOMATIC )        retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                 internalReturnValue;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monSts;

    retVal = E_NOT_OK;

    if( MonitorStatus != NULL_PTR )
    {
        monSts = (Dem_MonitorStatusType)0U;         /*  out parameter.  */
        internalReturnValue = Dem_Control_GetMonitorStatus( EventId, &monSts );

        if( internalReturnValue == DEM_IRT_OK )
        {
            *MonitorStatus = monSts;                /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}
#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_GetActiveFault                                       */
/* Description   | Gets the current aging counter of an event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [out] ActiveFaultPtr :                                   */
/*               |        Pointer to the area to get active fault data.     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK      : success.                              */
/*               |        E_NOT_OK  : failed.                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) ActiveFaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) activeFault;

    retVal = E_NOT_OK;

    if( ActiveFaultPtr != NULL_PTR )
    {
        activeFault = (boolean)FALSE;                 /*  out paramter.   */
        internalReturnValue = Dem_Control_GetActiveFault( EventId , &activeFault );
        if( internalReturnValue == DEM_IRT_OK )
        {
            *ActiveFaultPtr = activeFault;            /*  set value to out parameter. */
            retVal = E_OK;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
