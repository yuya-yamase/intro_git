/* Dem_DTC_DTCStatus_Output_c(v5-7-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_DTCStatus_Output/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Data_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Pm_DataCtl.h"
#include "../../../../inc/Dem_Pm_Misfire.h"

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
/* Function Name | Dem_DTC_GetDTCStatusOfEvent                              */
/* Description   | Get status of DTC by EventStrgIndex.                     */
/* Preconditions | -                                                        */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Identifier to specify the event record including  */
/*               |         the DTC status.                                  */
/*               | [out] DTCStatusPtr :                                     */
/*               |        UDS DTC statu byte                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : to get status of DTC was successful- */
/*               |        .                                                 */
/*               |        DEM_IRT_NG : to get status of DTC failed.         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusOfEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetStatus;

    retVal = DEM_IRT_NG;

    /* Calculation of statusOfDTC */
    resultGetStatus = Dem_Data_GetDTCStatus( EventStrgIndex, DTCStatusPtr );

    if( resultGetStatus == DEM_IRT_OK )
    {
        /* Translate the DTCStatus that got for the outside output. */
        retVal = Dem_DTC_TranslateDTCStatusForOutput( EventStrgIndex, DTCStatusPtr );
    }

    if( retVal != DEM_IRT_OK )
    {
        /* Output a fixation value because it is failure to get necessary information */
        (*DTCStatusPtr) =   DEM_DTCSTATUS_BYTE_DEFAULT;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByUdsDTC                             */
/* Description   | Gets the status of a DTC.                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_NG : DTC failed                           */
/*               |        DEM_IRT_WRONG_DTC : Wrong DTC                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByUdsDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetStatus;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
    VAR( boolean, AUTOMATIC ) retDTCClearTarget;

    /* Gets EventStrgIndex corresponding to DTC */
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    resultGetEvent = Dem_DataAvl_GetEventStrgIndexByDTC( DTCValue, &eventStrgIndex, &misfireCylinderNumber );   /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */

    retVal = DEM_IRT_NG;

    if( resultGetEvent == DEM_IRT_OK )
    {
        retDTCClearTarget = Dem_DTC_JudgeDTCClearTarget( eventStrgIndex );
        if( retDTCClearTarget == (boolean)FALSE )
        {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]   */
            if ( misfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
            {
                *DTCStatusPtr   =   Dem_Misfire_GetCylinderDTCStatus( misfireCylinderNumber );
                retVal          =   DEM_IRT_OK;
            }
            else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
            {
                /* Calculation of statusOfDTC */
                resultGetStatus = Dem_DTC_GetDTCStatusByDTC( eventStrgIndex, DTCStatusPtr );

                if( resultGetStatus == DEM_IRT_OK )
                {
                    /* Translate the DTCStatus that got for the outside output. */
                    retVal = Dem_DTC_TranslateDTCStatusForOutputByDTC( eventStrgIndex, DTCStatusPtr );
                }
            }
        }
        else
        {
            /*--------------------------------------*/
            /*  set default statusOfDTC.            */
            /*--------------------------------------*/
            (*DTCStatusPtr) =   DEM_DTCSTATUS_BYTE_DEFAULT;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]   */
            if ( misfireCylinderNumber != DEM_MISFIRE_CYL_NUM_INVALID )
            {
                /*  no process at misfire event.    */
            }
            else
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )          */
            {
                Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit( eventStrgIndex, DTCStatusPtr );
            }
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* Getting of EventStrgIndex corresponding to DTC failed */
        retVal = DEM_IRT_WRONG_DTC;
    }

    if( retVal != DEM_IRT_OK )
    {
        /* Output a fixation value because it is failure to get necessary information */
        (*DTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusAndUdsDTC                            */
/* Description   | Gets DTC and Status                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of DTC and status was successful */
/*               |        DEM_IRT_NG : get of DTC and status failed         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DTC_GetDTCAndStatus(v5-3-0).             */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusAndUdsDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetStatus;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = DEM_IRT_NG;

    retGetDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, DTCValuePtr );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    if( retGetDTC == DEM_IRT_OK )
    {
        retDTCClerTarget = Dem_DTC_JudgeDTCClearTarget( EventStrgIndex );                   /* [GUD]EventStrgIndex */
        if( retDTCClerTarget == (boolean)FALSE )
        {
            resultGetStatus = Dem_DTC_GetDTCStatusByDTC( EventStrgIndex, DTCStatusPtr );    /* [GUD]EventStrgIndex */

            if( resultGetStatus == DEM_IRT_OK )
            {
                /* Translate the DTCStatus that got for the outside output. */
                retVal = Dem_DTC_TranslateDTCStatusForOutputByDTC( EventStrgIndex, DTCStatusPtr );      /* [GUD]EventStrgIndex */
            }
        }
        else
        {
            /*--------------------------------------*/
            /*  set default statusOfDTC.            */
            /*--------------------------------------*/
            (*DTCStatusPtr) =   DEM_DTCSTATUS_BYTE_DEFAULT;

            Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit( EventStrgIndex, DTCStatusPtr );          /* [GUD]EventStrgIndex */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusAndUdsDTC_forFilDTC                  */
/* Description   | Gets DTC and Status                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event                                */
/*               | [in] DTCStatusMask :                                     */
/*               |        DTCStatusMask.                                    */
/*               | [in] FilterWithSeverity :                                */
/*               |        FilterWithSeverity.                               */
/*               | [in] DTCSeverityMask :                                   */
/*               |        Severity mask.                                    */
/*               | [out] DTCValuePtr :                                      */
/*               |        DTC value .                                       */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The DTC status byte which has been retrieved.     */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        Severity information.                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of DTC and status was successful */
/*               |        DEM_IRT_NG : get of DTC and status failed         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DTC_GetDTCStatusAndUdsDTC.     */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusAndUdsDTC_forFilDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetStatus;

    retVal = DEM_IRT_NG;

    retGetDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( EventStrgIndex, DTCValuePtr );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    if( retGetDTC == DEM_IRT_OK )
    {
        /*--------------------------------------------------*/
        /*  Get statusOfDTC and severity.                   */
        /*  check EventAvailable status in Dem_DTC_GetDTCStatusByDTCAndSeverity().  */
        /*  Merge WIRStatus is in Dem_DTC_GetDTCStatusByDTCAndSeverity().           */
        /*--------------------------------------------------*/
        /*  severity target data.   */
        resultGetStatus = Dem_DTC_GetDTCStatusByDTCAndSeverity( EventStrgIndex, DTCStatusMask, FilterWithSeverity, DTCSeverityMask, DTCStatusPtr, DTCSeverityPtr );    /* [GUD]EventStrgIndex */

        if( resultGetStatus == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;

        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
