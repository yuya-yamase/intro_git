/* Dem_Dcm_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
/* Function Name | Dem_DcmSetEDRNumberFilter                                */
/* Description   | Sets the extended data record number filter.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | Dem_ReturnSetFilterType                                  */
/*               |        DEM_FILTER_ACCEPTED : accepted                    */
/*               |        DEM_WRONG_CONDITION : wrong condition.            */
/*               |        DEM_WRONG_FILTER : wrong filter                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetEDRNumberFilter
(
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnSetFilterType, AUTOMATIC ) retVal;

    retVal = DEM_WRONG_FILTER;

    internalReturnValue = Dem_Control_SetEDRNumberFilter( (Dem_u08_EDRRecordNumberType)ExtendedDataNumber );

    /* Convert return value */
    if( internalReturnValue == DEM_IRT_OK )
    {
        retVal = DEM_FILTER_ACCEPTED;
    }
    else if( internalReturnValue == DEM_IRT_WRONG_CONDITION )
    {
        retVal = DEM_WRONG_CONDITION;
    }
    else
    {
        /*  DEM_WRONG_FILTER.   */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DcmGetNextEDRNumFilteredDTC                          */
/* Description   | Gets the next filtered DTC matching the filter criteria- */
/*               | . For UDS services, the interface has an asynchronous b- */
/*               | ehavior, because a large number of DTCs has to be proce- */
/*               | ssed.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCPtr :                                           */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC. It follows the format as de- */
/*               |        fined in ISO14229-1 If the return value of the f- */
/*               |        unction call is other than DEM_FILTERED_OK this - */
/*               |        parameter does not contain valid data.            */
/* Return Value  | Dem_ReturnGetNextFilteredElementType                     */
/*               |        DEM_FILTERED_OK : success                         */
/*               |        DEM_FILTERED_NO_MATCHING_ELEMENT : no matching    */
/*               |        DEM_FILTERED_PENDING : pending                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextEDRNumFilteredDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNextFilteredElementType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) status;

    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;

    if( DTCPtr == NULL_PTR )
    {
        /* No Process */
    }
    else if( DTCStatusPtr == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtcvalue = (Dem_u32_DTCValueType)0U;                  /*  out parameter.  */
        status   = (Dem_UdsStatusByteType)0U;   /*  out parameter.  */
        internalReturnValue = Dem_Control_GetNextEDRNumFilteredDTC( &dtcvalue , &status );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTCPtr       = dtcvalue;       /*  set value to out parameter. */
                *DTCStatusPtr = status;         /*  set value to out parameter. */
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
