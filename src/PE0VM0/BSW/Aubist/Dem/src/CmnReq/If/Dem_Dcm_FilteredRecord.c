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
/* Function Name | Dem_DcmSetFreezeFrameRecordFilter                        */
/* Description   | Sets a freeze frame record filter.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls.              */
/*               | [out] NumberOfFilteredRecords :                          */
/*               |        Number of freeze frame records currently stored - */
/*               |        in the event memory.                              */
/* Return Value  | Dem_ReturnSetFilterType                                  */
/*               |        DEM_FILTER_ACCEPTED : accepted                    */
/*               |        DEM_WRONG_FILTER : wrong filter                   */
/*               |        DEM_WRONG_CONDITION : wrong condtion              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetFreezeFrameRecordFilter
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredRecords
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnSetFilterType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) number;

    retVal = DEM_WRONG_FILTER;

    if( NumberOfFilteredRecords != NULL_PTR )
    {
        number = (Dem_u08_FFDIndexType)0U;    /*  out parameter.  */
        internalReturnValue = Dem_Control_SetFreezeFrameRecordFilter( DTCFormat , &number );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *NumberOfFilteredRecords = (uint16)number;  /*  set value to out parameter. */
                retVal = DEM_FILTER_ACCEPTED;
                break;
            case DEM_IRT_WRONG_CONDITION:
                retVal = DEM_WRONG_CONDITION;
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
/* Function Name | Dem_DcmGetNextFilteredRecord                             */
/* Description   | Gets the next freeze frame record number and its associ- */
/*               | ated DTC stored in the event memory. The interface has - */
/*               | an asynchronous behavior, because NvRAM access might be  */
/*               |  required.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTC :                                              */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function. If the retu- */
/*               |        rn value of the function is other than DEM_FILTE- */
/*               |        RED_OK this parameter does not contain valid dat- */
/*               |        a.                                                */
/*               | [out] RecordNumber :                                     */
/*               |        Freeze frame record number of the reported DTC (- */
/*               |        relative addressing). If the return value of the  */
/*               |         function is other than DEM_FILTERED_OK this par- */
/*               |        ameter does not contain valid data.               */
/* Return Value  | Dem_ReturnGetNextFilteredElementType                     */
/*               |        DEM_FILTERED_OK : success                         */
/*               |        DEM_FILTERED_NO_MATCHING_ELEMENT : no matching    */
/*               |        DEM_FILTERED_PENDING : pending                    */
/*               |        DEM_FILTERED_BUFFER_TOO_SMALL : buffer too small  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredRecord
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumber
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalReturnValue;
    VAR( Dem_ReturnGetNextFilteredElementType, AUTOMATIC ) retVal;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcvalue;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recnumber;

    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;

    if( DTC == NULL_PTR )
    {
        /* No Process */
    }
    else if( RecordNumber == NULL_PTR )
    {
        /* No Process */
    }
    else
    {
        dtcvalue  = (Dem_u32_DTCValueType)0U; /*  out parameter.  */
        recnumber = (uint8)0U;  /*  out parameter.  */
        internalReturnValue = Dem_Control_GetNextFilteredRecord( &dtcvalue , &recnumber );

        /* Convert return value */
        switch( internalReturnValue )
        {
            case DEM_IRT_OK:
                *DTC          = dtcvalue;   /*  set value to out parameter. */
                *RecordNumber = (uint8)recnumber;  /*  set value to out parameter. */
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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
