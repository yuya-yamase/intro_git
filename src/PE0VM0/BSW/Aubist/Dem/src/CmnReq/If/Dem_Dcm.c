/* Dem_Dcm_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

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
/* Function Name | Dem_DcmGetDTCStatusAvailabilityMask                      */
/* Description   | Gets the DTC Status availability mask.                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusMask :                                    */
/*               |        DTCStatusMask The value DTCStatusMask indicates - */
/*               |        the supported DTC status bits from the Dem. All - */
/*               |        supported information is indicated by setting th- */
/*               |        e corresponding status bit to 1. See ISO14229-1.  */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from. If passed value d- */
/*               |        oes not fit to Configuration, the DET error DEM_- */
/*               |        E_WRONG_CONFIGURATION shall be reported, e.g. if  */
/*               |         DTCOrigin "DEM_DTC_ORIGIN_MIRROR_MEMORY" is pas- */
/*               |        sed, but no mirror memory is configured.          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of DTC status mask was successful      */
/*               |        E_NOT_OK : get of DTC status mask failed          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) mask;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;

    retVal = E_NOT_OK;

    if( DTCStatusMask != NULL_PTR )
    {
        mask = (Dem_UdsStatusByteType)0U;   /*  out parameter.  */

        internalReturnValue =   Dem_CfgInfoCmn_GetDTCStatusAvailabilityMask( &mask, DTCOrigin );

        *DTCStatusMask = mask;  /*  set value to out parameter. */
        if ( internalReturnValue == DEM_IRT_OK )
        {
            retVal = E_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetDTCSeverityAvailabilityMask                    */
/* Description   | Gets the DTC Severity availability mask.                 */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCSeverityMask :                                  */
/*               |        The value DTCSeverityMask indicates the support - */
/*               |        ed DTC severity bits from the Dem. All supporte - */
/*               |        d information is indicated by setting the corre - */
/*               |        sponding status bit to 1. See ISO14229-1.       - */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : get of DTC severity mask was successful    */
/*               |        E_NOT_OK : get of DTC severity mask failed        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCSeverityAvailabilityMask
(
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCSeverityMask
)
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) mask;

    retVal = E_NOT_OK;

    if( DTCSeverityMask != NULL_PTR )
    {
        mask = (Dem_DTCSeverityType)0U;   /*  out parameter.  */
        Dem_CfgInfoPm_GetDTCSeverityAvailabilityMask( &mask );

        *DTCSeverityMask = mask;  /*  set value to out parameter. */
        retVal = E_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetStatusOfDTC                                    */
/* Description   | Gets the status of a DTC. For large configurations and - */
/*               | DTC-calibration, the interface behavior can be asynchro- */
/*               | nous (splitting the DTC-search into segments). The DTCs  */
/*               |  of OBD Events Suppression shall be reported as DEM_STA- */
/*               | TUS_WRONG_DTC.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTC :                                               */
/*               |        Diagnostic Trouble Code in UDS format.            */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from.                    */
/*               | [out] DTCStatus :                                        */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. If the return value of the - */
/*               |        function call is other than DEM_STATUS_OK this p- */
/*               |        arameter does not contain valid data. 0x00...0xF- */
/*               |        F match DTCStatusMask as defined in ISO14229-1    */
/* Return Value  | Dem_ReturnGetStatusOfDTCType                             */
/*               |        DEM_STATUS_OK : success                           */
/*               |        DEM_STATUS_WRONG_DTC : wrong DTC                  */
/*               |        DEM_STATUS_WRONG_DTCORIGIN : wrong DTC origin     */
/*               |        DEM_STATUS_FAILED : failed                        */
/*               |        DEM_STATUS_PENDING : pending                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetStatusOfDTCType, DEM_CODE ) Dem_DcmGetStatusOfDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DTCStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetStatusOfDTCType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) status;

    retVal = DEM_STATUS_FAILED;

    if( DTCStatus != NULL_PTR )
    {
        status = (uint8)0U;     /*  out parameter.  */
        internalReturnValue = Dem_ControlIFCmn_GetStatusOfDTC( (Dem_u32_DTCValueType)DTC , DTCOrigin , &status );
        *DTCStatus = status;    /*  set value to out parameter. */

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                retVal = DEM_STATUS_OK;
                break;
            case DEM_IRT_WRONG_DTC:
                retVal = DEM_STATUS_WRONG_DTC;
                break;
            case DEM_IRT_WRONG_DTCORIGIN:
                retVal = DEM_STATUS_WRONG_DTCORIGIN;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_STATUS_PENDING;
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
/* Function Name | Dem_DcmGetTranslationType                                */
/* Description   | Gets the supported DTC formats of the ECU.The supported  */
/*               |  formats are configured via DemTypeOfDTCSupported.       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_DTCTranslationFormatType                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_DTCTranslationFormatType, DEM_CODE ) Dem_DcmGetTranslationType
( void )
{
    VAR( Dem_DTCTranslationFormatType, AUTOMATIC ) retVal;

    retVal = Dem_CfgInfo_GetTranslationType();

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
