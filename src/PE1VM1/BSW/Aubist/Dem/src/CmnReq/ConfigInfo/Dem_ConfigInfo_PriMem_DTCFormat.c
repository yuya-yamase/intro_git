/* Dem_ConfigInfo_PriMem_DTCFormat_c(v5-8-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_PriMem_DTCFormat/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCFormat                               */
/* Description   | Checks the consistency of the specified DTCFormat type.  */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        The specified DTCFormat type to check consistenc- */
/*               |        y.                                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The consistency checking of DTCForm- */
/*               |        at type is successful.                            */
/*               |        DEM_IRT_NG : The consistency checking of DTCForm- */
/*               |        at type is failed.                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CheckDTCFormat
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    if ( DTCFormat == DEM_DTC_FORMAT_UDS )
    {
        retVal = DEM_IRT_OK;
    }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )            /*  [FuncSw]    */
    else if ( DTCFormat == DEM_DTC_FORMAT_OBD )
    {
        retVal = DEM_IRT_OK;
    }
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )     */
    else
    {
        /* no processing. */
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
