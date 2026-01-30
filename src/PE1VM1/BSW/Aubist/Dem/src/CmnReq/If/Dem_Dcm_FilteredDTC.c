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
/* Function Name | Dem_DcmSetDTCFilter                                      */
/* Description   | Sets the DTC Filter. The server shall perform a bit-wis- */
/*               | e logical AND-ing operation between the parameter DTCSt- */
/*               | atusMask and the current DTC status in the server. In a- */
/*               | ddition to the DTCStatusAvailabilityMask, the server sh- */
/*               | all return all DTCs for which the result of the AND-ing  */
/*               |  operation is non-zero [i.e. (statusOfDTC & DTCStatusMa- */
/*               | sk) != 0]. The server shall process only the DTC Status  */
/*               |  bits that it is supporting. OBD Events Suppression sha- */
/*               | ll be ignored for this computation. If no DTCs within t- */
/*               | he server match the masking criteria specified in the c- */
/*               | lient's request, no DTC or status information shall be - */
/*               | provided following the DTCStatusAvailabilityMask byte i- */
/*               | n the positive response message (((statusOfDTC & DTCSta- */
/*               | tusMask) != 0) && ((severity & DTCSeverityMask) != 0)) - */
/*               | == TRUE                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               |        Status-byte mask for DTC status-byte filtering V- */
/*               |        alues:0x00: Autosar-specific value to deactivate  */
/*               |         the status-byte filtering (different meaning th- */
/*               |        an in ISO 14229-1) to report all supported DTCs - */
/*               |        (used for service 0x19 subfunctions 0x0A/0x15) 0- */
/*               |        x01..0xFF: Status-byte mask according to ISO 142- */
/*               |        29-1 DTCStatusMask (handed over by Dcm from serv- */
/*               |        ice request directly) to filter for DTCs with at  */
/*               |         least one status bit set matching this status-b- */
/*               |        yte mask                                          */
/*               | [in] DTCKind :                                           */
/*               |        Defines the functional group of DTCs to be repor- */
/*               |        ted (e.g. all DTC, OBD-relevant DTC). If passed - */
/*               |        value does not fit to Configuration, the DET err- */
/*               |        or DEM_E_WRONG_CONFIGURATION shall be reported, - */
/*               |        e.g if DTCKind "DEM_DTC_KIND_EMISSION_REL_DTCS" - */
/*               |        is passed, but no emission related DTCs are conf- */
/*               |        igured.                                           */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls. If passed v- */
/*               |        alue does not fit to Configuration, the DET erro- */
/*               |        r DEM_E_WRONG_CONFIGURATION shall be reported, e- */
/*               |        .g. if DTCFormat "DEM_DTC_FORMAT_OBD" is passed,  */
/*               |         but OBD is not supported per configuration.      */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from. If passed value d- */
/*               |        oes not fit to Configuration, the DET error DEM_- */
/*               |        E_WRONG_CONFIGURATION shall be reported, e.g. if  */
/*               |         DTCOrigin "DEM_DTC_ORIGIN_MIRROR_MEMORY" is pas- */
/*               |        sed, but no mirror memory is configured.          */
/*               | [in] FilterWithSeverity :                                */
/*               |        This flag defines whether severity information (- */
/*               |        ref. to parameter below) shall be used for filte- */
/*               |        ring. This is to allow for coexistence of DTCs w- */
/*               |        ith and without severity information.             */
/*               | [in] DTCSeverityMask :                                   */
/*               |        This parameter contains the DTCSeverityMask acco- */
/*               |        rding to ISO14229-1 (see for example Service 0x1- */
/*               |        9, subfunction 0x08). If the value is invalid th- */
/*               |        e function returns DEM_WRONG_FILTER.              */
/*               | [in] FilterForFaultDetectionCounter :                    */
/*               |        This flag defines whether the fault detection co- */
/*               |        unter information shall be used for filtering. T- */
/*               |        his is to allow for coexistence of DTCs with and  */
/*               |         without fault detection counter information. If  */
/*               |         fault detection counter information is filter c- */
/*               |        riteria, only those DTCs with a fault detection - */
/*               |        counter value between 1 and 0x7E shall be report- */
/*               |        ed. Remark: If the event does not use the deboun- */
/*               |        cing inside Dem, then the Dem must request this - */
/*               |        information via GetFaultDetectionCounter.         */
/* Return Value  | Dem_ReturnSetFilterType                                  */
/*               |        DEM_FILTER_ACCEPTED : accepted                    */
/*               |        DEM_WRONG_FILTER : wrong filter                   */
/*               |        DEM_WRONG_CONDITION : wrong condition             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetDTCFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    VAR( boolean, AUTOMATIC ) FilterForFaultDetectionCounter
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnSetFilterType, AUTOMATIC ) retVal;

    retVal = DEM_WRONG_FILTER;

    internalReturnValue = Dem_Control_SetDTCFilter( DTCStatusMask , DTCKind , DTCFormat , DTCOrigin , FilterWithSeverity , DTCSeverityMask , FilterForFaultDetectionCounter );

    /* Convert return value */
    switch( internalReturnValue )
    {
        case DEM_IRT_OK:
            retVal = DEM_FILTER_ACCEPTED;
            break;
        case DEM_IRT_WRONG_CONDITION:
            retVal = DEM_WRONG_CONDITION;
            break;
        default:
            /* No Process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetNextFilteredDTC                                */
/* Description   | Gets the next filtered DTC matching the filter criteria- */
/*               | . For UDS services, the interface has an asynchronous b- */
/*               | ehavior, because a large number of DTCs has to be proce- */
/*               | ssed.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTC :                                              */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] DTCStatus :                                        */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. It follows the format as de- */
/*               |        fined in ISO14229-1 If the return value of the f- */
/*               |        unction call is other than DEM_FILTERED_OK this - */
/*               |        parameter does not contain valid data.            */
/* Return Value  | Dem_ReturnGetNextFilteredElementType                     */
/*               |        DEM_FILTERED_OK : success                         */
/*               |        DEM_FILTERED_NO_MATCHING_ELEMENT : no matching    */
/*               |        DEM_FILTERED_PENDING : pending                    */
/*               |        DEM_FILTERED_BUFFER_TOO_SMALL : buffer too small  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNextFilteredElementType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) status;

    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;

    if( DTC == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCStatus == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtcvalue = (Dem_u32_DTCValueType)0U;                  /*  out parameter.  */
        status   = (Dem_UdsStatusByteType)0U;   /*  out parameter.  */
        internalReturnValue = Dem_Control_GetNextFilteredDTC( &dtcvalue , &status );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTC       = dtcvalue;  /*  set value to out parameter. */
                *DTCStatus = status;    /*  set value to out parameter. */
                retVal = DEM_FILTERED_OK;
                break;
            case DEM_IRT_NO_MATCHING_ELEMENT:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_FILTERED_PENDING;
                break;
            default:
                /* No Process */
                break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetNextFilteredDTCAndSeverity                     */
/* Description   | Gets the next filtered DTC and its associated Severity - */
/*               | matching the filter criteria. The interface has an asy - */
/*               | asynchronous behavior, because a large number of DTCs  - */
/*               | has to be processed                                      */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTC :                                              */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] DTCStatus :                                        */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. It follows the format as de- */
/*               |        fined in ISO14229-1 If the return value of the f- */
/*               |        unction call is other than DEM_FILTERED_OK this - */
/*               |        parameter does not contain valid data.            */
/*               | [out] DTCSeverity :                                      */
/*               |        Receives the severity value returned by the func- */
/*               |        tion.If the return value of the function is othe- */
/*               |        r than DEM_FILTERED_OK this parameter does not c- */
/*               |        ontain valid data.                                */
/*               | [out] DTCFunctionalUnit                                  */
/*               |        Receives the functional unit value returned by t- */
/*               |        he function.If the return value of the function - */
/*               |        is other than DEM_FILTERED_OK this parameter doe- */
/*               |        s not contain valid data.                         */
/* Return Value  | Dem_ReturnGetNextFilteredElementType                     */
/*               |        DEM_FILTERED_OK : success                         */
/*               |        DEM_FILTERED_NO_MATCHING_ELEMENT : no matching    */
/*               |        DEM_FILTERED_PENDING : pending                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredDTCAndSeverity
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatus,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCSeverity,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DTCFunctionalUnit
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNextFilteredElementType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) status;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) severity;

    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;

    if( DTC == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCStatus == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCSeverity == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCFunctionalUnit == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtcvalue = (Dem_u32_DTCValueType)0U;                  /*  out parameter.  */
        status   = (Dem_UdsStatusByteType)0U;   /*  out parameter.  */
        severity = (Dem_DTCSeverityType)0U;     /*  out parameter.  */

        internalReturnValue = Dem_Control_GetNextFilteredDTCAndSeverity( &dtcvalue , &status , &severity );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTC       = dtcvalue;    /*  set value to out parameter. */
                *DTCStatus = status;      /*  set value to out parameter. */
                *DTCSeverity = severity;  /*  set value to out parameter. */
                *DTCFunctionalUnit = (uint8)0U;

                retVal = DEM_FILTERED_OK;
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_FILTERED_PENDING;
                break;
            default:
                /* DEM_IRT_NO_MATCHING_ELEMENT */
                /* No Process */
                break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetNumberOfFilteredDTC                            */
/* Description   | Gets the number of a filtered DTC.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfFilteredDTC :                              */
/*               |        The number of DTCs matching the defined status m- */
/*               |        ask.                                              */
/* Return Value  | Dem_ReturnGetNumberOfFilteredDTCType                     */
/*               |        DEM_NUMBER_OK : Getting number of filtered DTCs - */
/*               |        was successful.                                   */
/*               |        DEM_NUMBER_FAILED : Getting number of filtered D- */
/*               |        TCs failed.                                       */
/*               |        DEM_NUMBER_PENDING : The requested values is cal- */
/*               |        culated asynchronously and currently not availab- */
/*               |        le. The caller can retry later.                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE ) Dem_DcmGetNumberOfFilteredDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredDTC
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNumberOfFilteredDTCType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) number;

    retVal = DEM_NUMBER_FAILED;

    if( NumberOfFilteredDTC != NULL_PTR )
    {
        number = (uint16)0U;    /*  out parameter.  */
        internalReturnValue = Dem_Control_GetNumberOfFilteredDTC( &number );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *NumberOfFilteredDTC = number;  /*  set value to out parameter. */
                retVal = DEM_NUMBER_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_NUMBER_PENDING;
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
/* Function Name | Dem_DcmGetNumberOfFilteredDTCAndSeverity                 */
/* Description   | Gets the number of a filtered DTC.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfFilteredDTCAndSeverityPtr :                */
/*               |        The number of DTCs matching the defined status m- */
/*               |        ask.                                              */
/* Return Value  | Dem_ReturnGetNumberOfFilteredDTCType                     */
/*               |        DEM_NUMBER_OK : Getting number of filtered DTCs - */
/*               |        was successful.                                   */
/*               |        DEM_NUMBER_FAILED : Getting number of filtered D- */
/*               |        TCs failed.                                       */
/*               |        DEM_NUMBER_PENDING : The requested values is cal- */
/*               |        culated asynchronously and currently not availab- */
/*               |        le. The caller can retry later.                   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_DcmGetNumberOfFilteredDTC().   */
/****************************************************************************/
FUNC( Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE ) Dem_DcmGetNumberOfFilteredDTCAndSeverity
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredDTCAndSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNumberOfFilteredDTCType, AUTOMATIC ) retVal;
    VAR( uint16, AUTOMATIC ) number;

    retVal = DEM_NUMBER_FAILED;

    if( NumberOfFilteredDTCAndSeverityPtr != NULL_PTR )
    {
        number = (uint16)0U;    /*  out parameter.  */
        internalReturnValue = Dem_Control_GetNumberOfFilteredDTCAndSeverity( &number );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *NumberOfFilteredDTCAndSeverityPtr = number;  /*  set value to out parameter. */
                retVal = DEM_NUMBER_OK;
                break;
            case DEM_IRT_NG:
                /* No Process */
                break;
            case DEM_IRT_PENDING:
                retVal = DEM_NUMBER_PENDING;
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
