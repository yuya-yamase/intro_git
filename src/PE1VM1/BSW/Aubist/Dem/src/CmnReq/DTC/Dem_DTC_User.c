/* Dem_DTC_User_c(v5-3-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/DTC_User/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_CmnLib_DTC_User.h"

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


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat          */
/* Description   | Calls callout function "ClearEventAllowed" configured t- */
/*               | o "stubDemTranslateUserDefinedFormatCallOut".            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |       Identifier of the diagnosis event corresponding to */
/*               |       DTCStatus.                                         */
/*               | [in] OldDTCStatus :                                      */
/*               |       status of DTC before translation.                  */
/*               | [out] NewDTCStatusPtr :                                  */
/*               |        status of DTC after translation.                  */
/*               | [out] ResultOfCallbackPtr :                              */
/*               |        The result of calling of callout function.        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The callout function "DemTranslateS- */
/*               |        tatusOfDTCToUserDefinedFormat" calling is succes- */
/*               |        sful.                                             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_TranslateStatusOfDTCToUserDefinedFormat
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,           /* MISRA DEVIATION */
    VAR( Dem_UdsStatusByteType, AUTOMATIC) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr,
    P2VAR( Std_ReturnType, AUTOMATIC, AUTOMATIC ) ResultOfCallOutPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Sets old DTC status in new DTC status. */
    (*NewDTCStatusPtr) = OldDTCStatus;
    (*ResultOfCallOutPtr) = E_OK;
    retVal = DEM_IRT_OK;

    return( retVal );
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
