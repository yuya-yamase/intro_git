/* Dem_DTC_FilDTC_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/DTC_FilDTC/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../inc/Dem_CmnIf_DTC_FilDTC.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Udm_Data.h"
#include "../../../../usr/Dem_UserDTC_Callout.h"

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

static VAR( Dem_SetDTCFilterType, DEM_VAR_NO_INIT )  Dem_DTCFilter;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_GetDemDTCFlg;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_SetDTCFilter                                     */
/* Description   | The function set the DTC filter.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               |        Status-byte mask for DTC status-byte filtering V- */
/*               |        alues:0x00: Autosar-specific value to deactivate  */
/*               |         the status-byte filtering (different meaning th- */
/*               |        an in ISO 14229-1) to report all supported DTCs - */
/*               |        (used for service 0x19 subfunctions 0x0A/0x15) 0- */
/*               |        x01..0xFF:Status-byte mask according to ISO 1422- */
/*               |        9-1 DTCStatusMask (handed over by Dcm from servi- */
/*               |        ce request directly) to filter for DTCs with at - */
/*               |        least one status bit set matching this status-by- */
/*               |        te mask.                                          */
/*               | [in] DTCKind :                                           */
/*               |        Defines the functional group of DTCs to be repor- */
/*               |        ted (e.g. all DTC, OBD-relevant DTC).If passed v- */
/*               |        alue does not fit to Configuration, the DET erro- */
/*               |        r DEM_E_WRONG_CONFIGURATION shall be reported,e.- */
/*               |        g if DTCKind "DEM_DTC_KIND_EMISSION_REL_DTCS" is  */
/*               |         passed, but no emission related DTCs are config- */
/*               |        ured.                                             */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls.If passed va- */
/*               |        lue does not fit to Configuration, the DET error  */
/*               |         DEM_E_WRONG_CONFIGURATION shall be reported,e.g- */
/*               |        . if DTCFormat "DEM_DTC_FORMAT_OBD" is passed, b- */
/*               |        ut OBD is not supported per configuration.        */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from.If passed value do- */
/*               |        es not fit to Configuration, the DET error DEM_E- */
/*               |        _WRONG_CONFIGURATION shall be reported,e.g. if D- */
/*               |        TCOrigin "DEM_DTC_ORIGIN_MIRROR_MEMORY" is passe- */
/*               |        d, but no mirror memory is configured.            */
/*               | [in] FilterWithSeverity :                                */
/*               |        This flag defines whether severity information (- */
/*               |        ref to parameter below) shall be used for filter- */
/*               |        ing. This is to allow for coexistence of DTCs wi- */
/*               |        th and without severity information.              */
/*               | [in] DTCSeverityMask :                                   */
/*               |        This parameter contains the DTCSeverityMask acco- */
/*               |        rding to ISO14229-1 (see for example Service 0x1- */
/*               |        9, subfunction 0x08). If the value is invalid th- */
/*               |        e function returns DEM_WRONG_FILTER.              */
/*               | [in] FilterForFaultDetectionCounter :                    */
/*               |        This flag defines whether the fault detection co- */
/*               |        unter information shall be used for filtering.Th- */
/*               |        is is to allow for coexistence of DTCs with and - */
/*               |        without fault detection counter information.If f- */
/*               |        ault detection counter information is filter cri- */
/*               |        teria, only those DTCs with a fault detection co- */
/*               |        unter value between 1 and 0x7E shall be reported- */
/*               |        .Remark: If the event does not use the debouncin- */
/*               |        g inside Dem, then the Dem must request this inf- */
/*               |        ormation via GetFaultDetectionCounter.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SetDTCFilter
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
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultChkFltr;

    retVal = DEM_IRT_OK;

    resultChkFltr = Dem_CfgInfo_CheckDTCReadDTCParameter( DTCKind, DTCFormat, DTCOrigin );

    if( resultChkFltr == DEM_IRT_OK )
    {
        Dem_DTCFilter.DTCStatusMask                  = DTCStatusMask;
        Dem_DTCFilter.DTCFormat                      = DTCFormat;
        Dem_DTCFilter.DTCKind                        = DTCKind;
        Dem_DTCFilter.DTCOrigin                      = DTCOrigin;
        Dem_DTCFilter.FilterWithSeverity             = FilterWithSeverity;
        Dem_DTCFilter.DTCSeverityMask                = DTCSeverityMask;
        Dem_DTCFilter.FilterForFaultDetectionCounter = FilterForFaultDetectionCounter;

        if( ( DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
            /*  UserDefinedMemory   */
            retVal  =   Dem_UdmDTC_SetFilteredDTC( DTCStatusMask, DTCOrigin );
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
        }
        else
        {
            /*  primaryMemory or permanentMemory    */
            Dem_DTC_SetFilteredDTC( &Dem_DTCFilter );

            /*  set userDTC filter                  */
            Dem_SetUserDTCFilter( DTCStatusMask, DTCKind, DTCFormat, DTCOrigin, FilterWithSeverity, DTCSeverityMask, FilterForFaultDetectionCounter );

        }
        Dem_GetDemDTCFlg = (boolean)FALSE;

    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_RestartSetDTCFilter                              */
/* Description   | The function set the DTC filter.(re-start)               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_RestartSetDTCFilter
( void )
{
    (void)Dem_DTC_SetDTCFilter( Dem_DTCFilter.DTCStatusMask, Dem_DTCFilter.DTCKind, Dem_DTCFilter.DTCFormat, Dem_DTCFilter.DTCOrigin, Dem_DTCFilter.FilterWithSeverity, Dem_DTCFilter.DTCSeverityMask, Dem_DTCFilter.FilterForFaultDetectionCounter );  /* no return check required */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetNextFilteredDTC                               */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
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
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later.Only used by asynchro- */
/*               |        nous interfaces.                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) userDTCValue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) userDTCStatus;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) dtcSeverity; /* variable for commonization */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetUserDTC;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    if( Dem_GetDemDTCFlg == (boolean)FALSE )
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        if( ( Dem_DTCFilter.DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) == DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {
            /* search DTC for SID19-17 */
            retVal = Dem_UdmDTC_SearchFilteredDTC( Dem_DTCFilter.DTCStatusMask, Dem_DTCFilter.DTCOrigin, DTCValuePtr, DTCStatusPtr );
        }
        else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
        if( Dem_DTCFilter.DTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY )
        {
#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) /*  [FuncSw]    */
            retVal  =   Dem_DTC_SearchFilteredPFC( &Dem_DTCFilter, DTCValuePtr, DTCStatusPtr );
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */
        }
        else
        {
            if( Dem_DTCFilter.DTCFormat  == DEM_DTC_FORMAT_UDS )
            {
                retVal  =   Dem_DTC_SearchFilteredDTCAndSeverity( &Dem_DTCFilter, DTCValuePtr, DTCStatusPtr, &dtcSeverity );
            }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )     /*  [FuncSw]    */
            else if ( Dem_DTCFilter.DTCFormat == DEM_DTC_FORMAT_OBD )
            {
                retVal  =   Dem_DTC_SearchFilteredEdsDTC_byOrderList( &Dem_DTCFilter, DTCValuePtr, DTCStatusPtr );
            }
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )              */
            else
            {
                /*  no matching format.         */
            }
        }

        if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            Dem_GetDemDTCFlg = (boolean)TRUE;
        }
    }

    if( Dem_GetDemDTCFlg == (boolean)TRUE )
    {
        if( ( Dem_DTCFilter.DTCOrigin & DEM_DTC_ORIGIN_USERDEFINED_MEMORY ) != DEM_DTC_ORIGIN_USERDEFINED_MEMORY )
        {

            userDTCValue = DEM_DTC_VALUE_MIN;
            userDTCStatus = DEM_DTCSTATUS_BYTE_DEFAULT;
            dtcSeverity = DEM_DTCSEVERITY_BYTE_DEFAULT;

            /* Get the DTC information */
            retGetUserDTC = Dem_GetNextFilteredUserDTC( &userDTCValue, &userDTCStatus, &dtcSeverity );
            if( retGetUserDTC == DEM_FILTERED_OK )
            {
                retVal = DEM_IRT_OK;
                *DTCValuePtr = userDTCValue;
                *DTCStatusPtr = userDTCStatus;
            }
            else
            {
                /* No Process */
            }
        }
    }

    return retVal;

}

/****************************************************************************/
/* Function Name | Dem_DTC_GetNextFilteredDTCAndSeverity                    */
/* Description   | Gets the next filtered DTC and its severity              */
/* Preconditions | Dem_DTC_SetDTCFilter being executed.                     */
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
/*               | [out] DTCSeverity :                                      */
/*               |        Receives the severity value returned by the func- */
/*               |        tion.If the return value of the function is othe- */
/*               |        r than DEM_FILTERED_OK this parameter does not c- */
/*               |        ontain valid data.                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ting.                                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DTC_GetNextFilteredObdDTCAndSeverity(v5-3-0). */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTCAndSeverity
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) userDTCValue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) userDTCStatus;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) userDTCSeverity;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetUserDTC;

    VAR( boolean, AUTOMATIC ) modeSearchFromList;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    if( Dem_GetDemDTCFlg == (boolean)FALSE )
    {
        /*  check search mode.              */
        modeSearchFromList  =   (boolean)FALSE;

        if ( Dem_DTCFilter.DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS )
        {
            if( ( Dem_DTCFilter.DTCStatusMask == DEM_UDS_STATUS_PDTC )
             || ( Dem_DTCFilter.DTCStatusMask == DEM_UDS_STATUS_CDTC ) )
            {
                modeSearchFromList  =   (boolean)TRUE;
            }
        }

        if( modeSearchFromList == (boolean)TRUE )
        {
#if ( DEM_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
            /* search DTC from fault order list */
            retVal = Dem_DTC_SearchFilteredDTCAndSeverity_byOrderList( &Dem_DTCFilter, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )            */
        }
        else
        {
            /* search DTC from all event */
            retVal = Dem_DTC_SearchFilteredDTCAndSeverity( &Dem_DTCFilter, DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );
        }

        if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
        {
            Dem_GetDemDTCFlg = (boolean)TRUE;
        }
    }

    if( Dem_GetDemDTCFlg == (boolean)TRUE )
    {
        userDTCValue = DEM_DTC_VALUE_MIN;
        userDTCStatus = DEM_DTCSTATUS_BYTE_DEFAULT;
        userDTCSeverity = DEM_DTCSEVERITY_BYTE_DEFAULT;

        /* Get the DTC information */
        retGetUserDTC = Dem_GetNextFilteredUserDTC( &userDTCValue, &userDTCStatus, &userDTCSeverity );
        if( retGetUserDTC == DEM_FILTERED_OK )
        {
            retVal = DEM_IRT_OK;
            *DTCValuePtr = userDTCValue;
            *DTCStatusPtr = userDTCStatus;
            *DTCSeverityPtr = userDTCSeverity;
        }
    }

    return retVal;

}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
