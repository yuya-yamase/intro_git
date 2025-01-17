/* Dem_Clear_Callout_c(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Clear_Callout/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Clear_Callout.h"

#include "oxdocan_aubif.h"

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
/* Function Name | Dem_CheckClearCompleted                                  */
/* Description   | Check the clear status is completed.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] Caller :                                            */
/*               | [in] DTCValue : DTC value to be cleared                  */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the input-format of the provided DTC val- */
/*               |        ue                                                */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/* Return Value  | Dem_CalloutReturnType                                     */
/*               |        DEM_CALLOUT_OK : Completed                        */
/*               |        DEM_CALLOUT_PENDING : Processing                  */
/*               |        DEM_CALLOUT_NG : Failed... NRC 0x72               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_CalloutReturnType, DEM_CODE_CALLOUT ) Dem_CheckClearCompleted
(
    VAR( Dem_ClearDTCCallerType, AUTOMATIC ) Caller,
    VAR( uint32, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/

    vd_g_oXDoCANAubIfDtcEvmDeAct((uint8)OXDC_DTC_EVM_S14);
    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return DEM_CALLOUT_OK;
}


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
