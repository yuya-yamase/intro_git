/* Dem_UdmDTC_DTCStatus_Output_c(v5-8-0)                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/UdmDTC_DTCStatus/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../../inc/Dem_CmnLib_DTC_User.h"
#include "../../../../inc/Dem_Udm_DataAvl.h"
#include "../../../../inc/Dem_Udm_Data.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmDTC_CalculateDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

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
/* Function Name | Dem_UdmDTC_TranslateDTCstatusAfterUpdate                 */
/* Description   | Translation processing after the DTC status update.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Index corresponding to the event.                 */
/*               | [in/out] OldDTCStatusPtr :                               */
/*               |        DTC status before the event registration (it sto- */
/*               |        res a value after the translation processing for  */
/*               |         Out)                                             */
/*               | [in/out] NewDTCStatusPtr :                               */
/*               |        DTC status after the event registration (it stor- */
/*               |        es a value after the translation processing for - */
/*               |        Out)                                              */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_TranslateDTCStatusAfterUpdate
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    /* Gets EventId. */
    (void)Dem_CfgInfoUdm_CnvUdmEventIndexToEventId( UdmEventIndex, &eventId );  /* no return check required */

    /* Converts statusOfDTC into the format of the user definition. */
    (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*OldDTCStatusPtr), OldDTCStatusPtr, &resultOfCallOut );   /* no return check required */

    (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*NewDTCStatusPtr), NewDTCStatusPtr, &resultOfCallOut );   /* no return check required */


    /* Output old and new statusOfDTC except bits out of the support. */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_TranslateDTCStatusForOutput                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in/out] DTCStatusPtr :                                  */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_TranslateDTCStatusForOutput
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,              /* [PRMCHK:CALLER] */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallOut;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    resultOfCallOut = E_NOT_OK;

    /* Gets EventId */
    (void)Dem_CfgInfoUdm_CnvUdmEventIndexToEventId( UdmEventIndex, &eventId );  /* no return check required */

    /* Converts statusOfDTC into the format of the user definition. */
    (void)Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat( eventId, (*DTCStatusPtr), DTCStatusPtr, &resultOfCallOut );   /* no return check required */

    /* Output old and new statusOfDTC except bits out of the support. */

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    (*DTCStatusPtr) = Dem_DTC_CnvDTCStatus_ForOutput( (*DTCStatusPtr) );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_GetDTCStatusOfEvent                           */
/* Description   | Get status of DTC by EventIndex.                         */
/* Preconditions | UdmEventIndex is guarded at caller.                      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        Identifier to specify the event record including  */
/*               |         the DTC status.                                  */
/*               | [out] DTCStatusPtr :                                     */
/*               |        UDS DTC statu byte                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_GetDTCStatusOfEvent
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Calculation of statusOfDTC */
    Dem_UdmDTC_CalculateDTCStatus( UdmEventIndex, DTCStatusPtr );   /* [GUDCHK:CALLER]UdmEventIndex */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_GetDTCStatus                                  */
/* Description   | Gets the status of a DTC.                                */
/* Preconditions | UdmEventIndex is guarded at caller.                      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               | [in] DTCStatusAvailabilityMask :                         */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | branch changed.                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmDTC_GetDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,                  /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) retUdmDTCClearTarget;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) availabilityMaskDTCStatus;


    retUdmDTCClearTarget = Dem_UdmDTC_JudgeUdmDTCClearTargetOnClearProcessActive( UdmEventIndex );  /* [GUDCHK:CALLER]UdmEventIndex */
    if( retUdmDTCClearTarget == (boolean)FALSE )
    {
        /* Calculation of statusOfDTC */
        Dem_UdmDTC_CalculateDTCStatus( UdmEventIndex, DTCStatusPtr );           /* [GUDCHK:CALLER]UdmEventIndex */
    }
    else
    {
        *DTCStatusPtr = DEM_DTCSTATUS_BYTE_DEFAULT;
        Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr );  /* [GUDCHK:CALLER]UdmEventIndex */
    }

    /* mask it with statusOfDTC in DemDtcStatusAvailabilityMask. */
    availabilityMaskDTCStatus   =   DTCStatusAvailabilityMask;
    (*DTCStatusPtr) &= availabilityMaskDTCStatus;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_GetDTCAndStatus                               */
/* Description   | Gets DTC and Status                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventIndex :                                        */
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
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCAndStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,                  /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTCStatus;
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;

    retVal = DEM_IRT_NG;

    retGetDTC = Dem_UdmDataAvl_GetDTCByUdmEventIndex( UdmEventIndex, DEM_DTC_FORMAT_UDS, DTCValuePtr ); /* [GUDCHK:CALLER]UdmEventIndex */
    if( retGetDTC == DEM_IRT_OK )
    {
        retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTargetOnClearProcessActive( UdmEventIndex );
        if( retUdmDTCClerTarget == (boolean)FALSE )
        {
            retGetDTCStatus = Dem_UdmData_GetDTCStatus( UdmEventIndex, DTCStatusPtr );  /* [GUDCHK:CALLER]UdmEventIndex */
        }
        else
        {
            *DTCStatusPtr = DEM_DTCSTATUS_BYTE_DEFAULT ;
            retGetDTCStatus = DEM_IRT_OK;
        }

        if( retGetDTCStatus == DEM_IRT_OK )
        {
            Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr );      /* [GUDCHK:CALLER]UdmEventIndex */
            dtcStatusAvailabilityMask   =   DTCStatusAvailabilityMask;
            (*DTCStatusPtr) &= dtcStatusAvailabilityMask;
            retVal = DEM_IRT_OK;
        }
    }



    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmDTC_CalculateDTCStatus                            */
/* Description   |                                                          */
/* Preconditions | UdmEventIndex is guarded at caller.                      */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [out] DTCStatusPtr :                                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmDTC_CalculateDTCStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,              /* [PRMCHK:CALLER] */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Gets DTCStatus from event memory */
    (void)Dem_UdmData_GetDTCStatus( UdmEventIndex, DTCStatusPtr );  /* no return check required */  /* [GUDCHK:CALLER]UdmEventIndex */

    /* Translate the DTCStatus that got for the outside output. */
    Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr );                          /* [GUDCHK:CALLER]UdmEventIndex */

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


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
