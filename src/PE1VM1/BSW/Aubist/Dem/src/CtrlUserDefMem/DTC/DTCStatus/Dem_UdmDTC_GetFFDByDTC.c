/* Dem_UdmDTC_GetFFDByDTC_c(v5-8-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
FUNC( void, DEM_CODE ) Dem_UdmDTC_GetDTCStatusOfDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAvailabilityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) dtcStatusAvailabilityMask;

    retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTargetOnClearProcessActive( UdmEventIndex );
    if( retUdmDTCClerTarget == (boolean)FALSE )
    {
        /* Gets DTCStatus from the record update was disabled */
        Dem_UdmData_GetDTCStatusOfDisabledRecord( DTCStatusPtr );

    }
    else
    {
        *DTCStatusPtr = DEM_DTCSTATUS_BYTE_DEFAULT ;
    }

    /* Translate the DTCStatus that got for the outside output. */
    Dem_UdmDTC_TranslateDTCStatusForOutput( UdmEventIndex, DTCStatusPtr );

    /* Calculate DTCStatus */
    dtcStatusAvailabilityMask   =   DTCStatusAvailabilityMask;
    (*DTCStatusPtr) &= dtcStatusAvailabilityMask;

    return ;
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
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
