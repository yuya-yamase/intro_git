/* Dem_Control_FilteredEDR_c(v5-3-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FilteredEDR/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_EDR.h"
#include "Dem_Control_local.h"

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
/* Function Name | Dem_Control_SetEDRNumberFilter                           */
/* Description   | Sets the extended data record number filter.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Filter was accepted                  */
/*               |        DEM_IRT_WRONG_CONDITION : condition error.        */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Wrong record number. */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEDRNumberFilter
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkBehavior;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retFilter;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_WRONG_CONDITION;

    retCheckStatus = Dem_Control_ChkAfterCompleteInit();

    if( retCheckStatus == DEM_IRT_OK )
    {
        if( ( ExtendedDataNumber < DEM_EDR_RECNUM_01 ) || ( ExtendedDataNumber > DEM_EDR_RECNUM_EF ) )
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
            retFilter = Dem_EDR_SetEDRNumberFilter( ExtendedDataNumber );
            if( retFilter == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
            else
            {
                 checkBehavior = Dem_NotConfiguredDTCExtDataRecordNumberBehavior;
                 if ( checkBehavior == DEM_EDRNUM_ACCEPT)
                 {
                        retVal = DEM_IRT_OK;
                 }
                 else
                 {
                        retVal = DEM_IRT_WRONG_RECORDNUMBER;
                 }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetNextEDRNumFilteredDTC                     */
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
/*               |        ted and currently not available. The caller can   */
/*               |        retry later.                                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEDRNumFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*--------------------------------------------------------------------------*/
    /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
    /* These are the reasons why this function needs to get exclusive.          */
    /*  - This function call [DataMng] function directory.                      */
    /*  - This function called from SW-C/Dcm context.                           */
    /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
    SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_EventMemory();
    /*--------------------------------------------------------------------------*/
    retVal = Dem_EDR_GetNextEDRNumFilteredDTC( DTCValuePtr, DTCStatusPtr );

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
