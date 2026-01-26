/* Dem_DTC_CnvToOutputDTCStatus_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_CnvToOutputDTCStatus/CODE                         */
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

/****************************************************************************/
/* Function Name | Dem_DTC_CnvDTCStatus_PmAvailabilityMask                  */
/* Description   | convert the DTC status for output to Dcm.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusPtr : statusOfDTC                          */
/* Return Value  | Dem_UdsStatusByteType                                    */
/*               |              converted statusOfDTC.                      */
/* Notes         | used for output SID19 services.                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvDTCStatus_PmAvailabilityMask
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) availabilityMaskDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) outDTCStatus;

    /*  DemDTCStatusProductSupportBit   */
    outDTCStatus    =   Dem_DTC_CnvDTCStatus_ForOutput( DTCStatus );

    /*  DemDtcStatusAvailabilityMask    */
    availabilityMaskDTCStatus   =   Dem_DtcStatusAvailabilityMask;
    outDTCStatus    =   outDTCStatus & availabilityMaskDTCStatus;

    return outDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CnvDTCStatus_ForOutput                           */
/* Description   | convert the DTC status for output to SWC.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusPtr : statusOfDTC                          */
/* Return Value  | Dem_UdsStatusByteType                                    */
/*               |              converted statusOfDTC.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_DTC_CnvDTCStatus_ForOutput
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) productSupportDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) outDTCStatus;

    /*  DemDTCStatusProductSupportBit   */
    productSupportDTCStatus     =   Dem_DTCStatusProductSupportBit;
    outDTCStatus                =   DTCStatus & productSupportDTCStatus;

    return outDTCStatus;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CnvUpdateDTCStatus_ForOutput                     */
/* Description   | convert the DTC status for output to SWC.                */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] DTCStatusPtr : statusOfDTC                      */
/*               | [in/out] DTCStatusPtr : statusOfDTC                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_CnvUpdateDTCStatus_ForOutput
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) productSupportDTCStatus;

    /*  DemDTCStatusProductSupportBit   */
    productSupportDTCStatus     =   Dem_DTCStatusProductSupportBit;
    (*OldDTCStatusPtr)          =   (*OldDTCStatusPtr) & productSupportDTCStatus;
    (*NewDTCStatusPtr)          =   (*NewDTCStatusPtr) & productSupportDTCStatus;

    return ;
}


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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
