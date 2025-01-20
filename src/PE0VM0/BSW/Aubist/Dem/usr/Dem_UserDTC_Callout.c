/* Dem_UserDTC_Callout_c(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_UserDTC_Callout/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_UserDTC_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_SetUserDTCFilter                                     */
/* Description   | Set User DTC filter.                                     */
/* Preconditions | none                                                     */
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
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_SetUserDTCFilter
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
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return;
}



/****************************************************************************/
/* Function Name | Dem_GetNextFilteredUserDTC                               */
/* Description   | Gets the next filtered DTC matching the filter criteria- */
/*               | . For UDS services, the interface has an asynchronous b- */
/*               | ehavior, because a large number of DTCs has to be proce- */
/*               | ssed.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] UserDTCPtr :                                       */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] StatusOfDTCPtr :                                   */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. It follows the format as de- */
/*               |        fined in ISO14229-1 If the return value of the f- */
/*               |        unction call is other than DEM_FILTERED_OK this - */
/*               |        parameter does not contain valid data.            */
/*               | [out] SeverityPtr :                                      */
/*               |        Receives the severity value returned by the func- */
/*               |        tion.If the return value of the function is othe- */
/*               |        r than DEM_FILTERED_OK this parameter does not c- */
/*               |        ontain valid data.                                */
/* Return Value  | Dem_ReturnGetNextFilteredElementType                     */
/*               |        DEM_FILTERED_OK : success                         */
/*               |        DEM_FILTERED_NO_MATCHING_ELEMENT : no matching    */
/*               |        DEM_FILTERED_PENDING : pending                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE_CALLOUT ) Dem_GetNextFilteredUserDTC
(
    P2VAR( uint32, AUTOMATIC, AUTOMATIC ) UserDTCPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) StatusOfDTCPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) SeverityPtr
)
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
