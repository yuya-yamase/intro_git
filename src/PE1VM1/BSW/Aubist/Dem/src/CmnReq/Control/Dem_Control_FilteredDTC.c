/* Dem_Control_FilteredDTC_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FilteredDTC/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnIf_DTC_FilDTC.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( uint16, DEM_VAR_NO_INIT )  Dem_NumberOfFilteredDTC;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_SetDTCFilter                                 */
/* Description   | Sets DTC filter according to the specified conditions.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatusMask :                                     */
/*               |        Status-byte mask for DTC status-byte filtering    */
/*               | [in] DTCKind :                                           */
/*               |        Defines the functional group of DTCs to be repor- */
/*               |        ted                                               */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls               */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memory t- */
/*               |        his parameter is used to select the source memor- */
/*               |        y the DTCs shall be read from                     */
/*               | [in] FilterWithSeverity :                                */
/*               |        This flag defines whether severity information s- */
/*               |        hall be used for filtering                        */
/*               | [in] DTCSeverityMask :                                   */
/*               |        This parameter contains the DTCSeverityMask acco- */
/*               |        rding to ISO14229-1                               */
/*               | [in] FilterForFaultDetectionCounter :                    */
/*               |        This flag defines whether the fault detection co- */
/*               |        unter information shall be used for filtering     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_NG : Wrong filter selected                */
/*               |        DEM_IRT_WRONG_CONDITION : Wrong condtion          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDTCFilter
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
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStatus;

    retCheckStatus = Dem_Control_ChkAfterCompleteInit();
    if( retCheckStatus == DEM_IRT_OK )
    {
        Dem_NumberOfFilteredDTC = ((uint16)0x0000U);
        retVal = Dem_DTC_SetDTCFilter( DTCStatusMask, DTCKind, DTCFormat, DTCOrigin, FilterWithSeverity, DTCSeverityMask, FilterForFaultDetectionCounter );
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        retVal = DEM_IRT_WRONG_CONDITION;
    }

    return retVal;
}



/****************************************************************************/
/* Function Name | Dem_Control_GetNumberOfFilteredDTC                       */
/* Description   | Gets the number of a filtered DTC.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfFilteredDTCPtr :                           */
/*               |        The number of DTCs matching the defined status m- */
/*               |        ask.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Getting number of filtered DTCs was  */
/*               |         successful.                                      */
/*               |        DEM_IRT_NG : Getting number of filtered DTCs fai- */
/*               |        led.                                              */
/*               |        DEM_IRT_PENDING : The requested values is calcul- */
/*               |        ated asynchronously and currently not available.  */
/*               |         The caller can retry later.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTC
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) ret_DtcVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) ret_DtcStatus;

    retVal = DEM_IRT_NG;

    loopEnd = (boolean)FALSE;
    ret_DtcStatus = (Dem_UdsStatusByteType)0U;
    ret_DtcVal = (Dem_u32_DTCValueType)0U;

    while( loopEnd == (boolean)FALSE )
    {
        internalReturnValue = Dem_DTC_GetNextFilteredDTC( &ret_DtcVal , &ret_DtcStatus );

        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                Dem_NumberOfFilteredDTC = Dem_NumberOfFilteredDTC + (uint16)1U;
                break;
            case DEM_IRT_NO_MATCHING_ELEMENT:
                /* Loop End , Processing completion                         */
                loopEnd = (boolean)TRUE;
                *NumberOfFilteredDTCPtr = Dem_NumberOfFilteredDTC;  /*  set value to out parameter. */

                Dem_DTC_RestartSetDTCFilter();                      /*  reset data for restart.     */
                Dem_NumberOfFilteredDTC = ((uint16)0x0000U);

                retVal = DEM_IRT_OK;
                break;
            case DEM_IRT_PENDING:
                /* Loop End , Illegal Return Value                          */
                loopEnd = (boolean)TRUE;
                retVal = DEM_IRT_PENDING;
                break;
            default:
                /* Loop End , Illegal Return Value                          */
                loopEnd = (boolean)TRUE;
                break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetNumberOfFilteredDTCAndSeverity            */
/* Description   | Gets the number of a filtered DTC.                       */
/* Preconditions | none                                                     */
/* Parameters    | [out] NumberOfFilteredDTCAndSeverityPtr :                */
/*               |        The number of DTCs matching the defined status m- */
/*               |        ask.                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Getting number of filtered DTCs was  */
/*               |         successful.                                      */
/*               |        DEM_IRT_NG : Getting number of filtered DTCs fai- */
/*               |        led.                                              */
/*               |        DEM_IRT_PENDING : The requested values is calcul- */
/*               |        ated asynchronously and currently not available.  */
/*               |         The caller can retry later.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetNumberOfFilteredDTC().*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTCAndSeverity
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCAndSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) ret_DtcVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) ret_DtcStatus;
    VAR( Dem_DTCSeverityType, AUTOMATIC ) ret_DTCSeverity;

    retVal = DEM_IRT_NG;

    loopEnd = (boolean)FALSE;
    ret_DtcStatus = (Dem_UdsStatusByteType)0U;
    ret_DtcVal = (Dem_u32_DTCValueType)0U;

    while( loopEnd == (boolean)FALSE )
    {
        internalReturnValue = Dem_DTC_GetNextFilteredDTCAndSeverity( &ret_DtcVal , &ret_DtcStatus, &ret_DTCSeverity );

        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                Dem_NumberOfFilteredDTC = Dem_NumberOfFilteredDTC + (uint16)1U;
                break;
            case DEM_IRT_NO_MATCHING_ELEMENT:
                /* Loop End , Processing completion                         */
                loopEnd = (boolean)TRUE;
                *NumberOfFilteredDTCAndSeverityPtr = Dem_NumberOfFilteredDTC;  /*  set value to out parameter. */

                Dem_DTC_RestartSetDTCFilter();                                  /*  reset data for restart.     */
                Dem_NumberOfFilteredDTC = ((uint16)0x0000U);

                retVal = DEM_IRT_OK;
                break;
            case DEM_IRT_PENDING:
                /* Loop End , Illegal Return Value                          */
                loopEnd = (boolean)TRUE;
                retVal = DEM_IRT_PENDING;
                break;
            default:
                /* Loop End , Illegal Return Value                          */
                loopEnd = (boolean)TRUE;
                break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetNextFilteredDTC                           */
/* Description   | Gets the next filtered DTC which match the filter crite- */
/*               | ria.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |         DTC                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available. - */
/*               |        The caller can retry later. Only used by asynchr- */
/*               |        onous interfaces.                                 */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_DTC_GetNextFilteredDTC( DTCValuePtr, DTCStatusPtr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetNextFilteredDTCAndSeverity                */
/* Description   | Gets the next filtered DTC which match the filter crite- */
/*               | ria.                                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function               */
/*               | [out] DTCStatusPtr :                                     */
/*               |        receives the status information of the requested  */
/*               |         DTC                                              */
/*               | [out] DTCSeverityPtr :                                   */
/*               |        receives the severity of the requested DTC        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ting.                                             */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTCAndSeverity
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_DTC_GetNextFilteredDTCAndSeverity( DTCValuePtr, DTCStatusPtr, DTCSeverityPtr );

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
