/* Dem_UserDTC_OBD_Callout_c(v5-10-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_UserDTC_OBD_Callout/CODE                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_UserDTC_OBD_Callout.h"

#if ( DEM_USERDTC_GETNUMBEROFUSERDTC_CALLOUT_USE == STD_ON )

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
/* Function Name | Dem_GetNumberOfUserDTC                                   */
/* Description   | Get Number of UserDTC and MIL Lights up On/Off           */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCKind :                                           */
/*               |        Defines the functional group of DTCs to be repor- */
/*               |        ted (e.g. all DTC, OBD-relevant DTC). If passed - */
/*               |        value does not fit to Configuration, the DET err- */
/*               |        or DEM_E_WRONG_CONFIGURATION shall be reported, - */
/*               |        e.g if DTCKind "DEM_DTC_KIND_EMISSION_REL_DTCS" - */
/*               |        is passed, but no emission related DTCs are conf- */
/*               |        igured.                                           */
/*               | [Out] DTCNumPtr :                                        */
/*               |        DTC Number                                        */
/* Return Value  | void                                                     */
/*               |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_GetNumberOfUserDTC
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DTCNumPtr
)
{

    /**********************************************/
    /* The operation start that a user defined.   */
    /**********************************************/
    *DTCNumPtr = 0x00U;

    /**********************************************/
    /* The operation end that a user defined.     */
    /**********************************************/

    return;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDTC_GETNUMBEROFUSERDTC_CALLOUT_USE == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
