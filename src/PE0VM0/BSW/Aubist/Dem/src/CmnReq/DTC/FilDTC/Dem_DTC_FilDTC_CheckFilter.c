/* Dem_DTC_FilDTC_CheckFilter_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Dem_DTC_FilDTC_CheckFilter/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../inc/Dem_CmnLib_DTC_FilDTC.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* Function Name | Dem_DTC_CheckDTCAndSeverityForFilter                     */
/* Description   | check the filter and get is DTC and its severity         */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
/* Parameters    | [in] DTCFilterPtr :                                      */
/*               | [in] DTCStatus :                                         */
/*               | [in/out] DTCSeverity :                                   */
/*               |                  in  : target all severity class.        */
/*               |                  out : matched severity class.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : find matching element                */
/*               |        DEM_IRT_NG : not find matching element            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCAndSeverityForFilter
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkSeverity;

    VAR( boolean, AUTOMATIC ) checkMaskDTCStatus;

    retVal = DEM_IRT_NG;

    checkMaskDTCStatus  =   (boolean)FALSE;

    if( DTCFilterPtr->FilterWithSeverity == (boolean)TRUE )
    {
        /*  check severity      */
        retChkSeverity = Dem_DTC_CheckDTCSeverityForFilter( DTCFilterPtr->DTCSeverityMask, DTCSeverityPtr );
        if( retChkSeverity == DEM_IRT_OK )
        {
            /*  next : DTCStatusMask check  */
            checkMaskDTCStatus  =   (boolean)TRUE;
        }
    }
    else
    {
        /*  no severity check.              */
        /*  always check DTCStatusMask      */
        checkMaskDTCStatus  =   (boolean)TRUE;
    }

    if ( checkMaskDTCStatus == (boolean)TRUE )
    {
        retVal  =   Dem_DTC_CheckDTCStatusForFilter( DTCFilterPtr->DTCStatusMask, DTCStatus );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CheckDTCStatusForFilter                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               |                                                          */
/*               | [in] DTCStatusPtr :                                      */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCStatusForFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    /* check use DTC Mask */
    if( DTCStatusMask != DEM_DTCSTATUS_BYTE_ALL_OFF )
    {
        /* Mask the status Of DTC */
        /*  check target DTCstatus or not.  */
        if( ( DTCStatus & DTCStatusMask ) != ( Dem_UdsStatusByteType )0U )
        {
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* Consider DTCStatus to agree in a mask condition. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_CheckDTCSeverityForFilter                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCSeverityMask :                                   */
/*               |                                                          */
/*               | [in/out] DTCSeverityPtr :                                */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Data_CheckDTCSeverityForFilter(v5-3-0).  */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_CheckDTCSeverityForFilter
(
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) maskedSeverity;

    retVal = DEM_IRT_NG;

    /* Mask the severity */
    maskedSeverity = ( (*DTCSeverityPtr) & DTCSeverityMask & Dem_DtcSeverityAvailabilityMask );

    if( maskedSeverity != DEM_DTCSEVERITY_BYTE_ALL_OFF )
    {
        /* DTCSeverity which fits it in a mask condition. */
        (*DTCSeverityPtr) &= Dem_DtcSeverityAvailabilityMask;
        retVal = DEM_IRT_OK;
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
