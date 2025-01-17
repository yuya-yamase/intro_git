/* Dem_UdmDTC_GetFFDByDTC_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/UdmDTC_GetFFDByDTC/CODE                               */
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
#include "../../../../inc/Dem_Udm_Data.h"

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
/* Function Name | Dem_UdmDTC_GetDTCStatusOfDisabledRecord                  */
/* Description   | Get the DTC status of the record disabled from update.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               | [in] DTCStatusAvailabilityMask :                         */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status of DTC is OK                  */
/*               |        DEM_IRT_NG : DTC failed                           */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmDTC_GetDTCStatusOfDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultTransStatus;
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;

    retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTarget( UdmEventIndex );
    if( retUdmDTCClerTarget == (boolean)FALSE )
    {
        /* Gets DTCStatus from the record update was disabled */
        Dem_UdmData_GetDTCStatusOfDisabledRecord( DTCStatusPtr );

        /* Translate the DTCStatus that got for the outside output. */
        resultTransStatus = Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr );
    }
    else
    {
        *DTCStatusPtr = DEM_DTCSTATUS_BYTE_DEFAULT ;
        (void)Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr ); /* no return check required */
        resultTransStatus = DEM_IRT_OK;
    }

    if( resultTransStatus == DEM_IRT_OK )
    {
        /* Calculate DTCStatus */
        dtcStatusAvailabilityMask   =   DTCStatusAvailabilityMask;
        (*DTCStatusPtr) &= dtcStatusAvailabilityMask;
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* Outside output translatetion of the DTCStatus failed. */
        retVal = DEM_IRT_NG;
    }

    if( retVal == DEM_IRT_NG )
    {
        /*------------------------------------------*/
        /*  convert to output statusOfDTC.          */
        /*------------------------------------------*/
        (*DTCStatusPtr) = Dem_DTC_CnvDTCStatus_ForOutput( DEM_DTCSTATUS_BYTE_DEFAULT );
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
